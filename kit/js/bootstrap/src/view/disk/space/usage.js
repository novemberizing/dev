import React, { Component } from "react";
import axios from "axios";
import * as d3 from "d3";

const width = 800;
const height = 400;

const margin = {
    top: 25,
    bottom: 20,
    left: 65,
    right: 10
};

const x = d3.scaleLinear()
            .domain([0, 1])
            .range([margin.left, width - margin.right]);

export default class DiskSpaceUsageView extends Component {
    static parse(value) {
        return value.split(/\r?\n/)
                    .filter((o, index) => index > 0 && o)
                    .map(o => {
                        const strings = o.split(/\s+/);
                        return {
                            fs: strings[0],
                            size: strings[1],
                            used: strings[2],
                            avail: strings[3],
                            percent: strings[4],
                            mounted: strings.slice(5).join(" ")
                        };
                    });
    }
    constructor(props) {
        super(props);

        this.state = {
            histories: [],
            latest: null
        };

        this.histories = [];
        this.latest = null;
        this.svg = null;
        this.y = null;
        this.chart = null;

        this.onUsage = this.onUsage.bind(this);

        setInterval(() => {
            axios.get("http://192.168.0.124:8092/api/disk/space/usage", { headers: { "Content-Type": "application/json" } })
            .then(o => this.onUsage(o.data))
            .catch(e => console.log(e));
        }, 1000);
    }

    componentDidMount() {
        this.svg.append("g").call(g => g.attr("transform", `translate(0,${margin.top})`)
                                        .call(d3.axisTop(x)
                                                .ticks(10, "%"))
                                        .call(g => g.select(".domain").remove()));
    }

    onUsage(histories) {
        histories = histories.map(o => {
            return {
                clock: o.clock,
                nanosecond: o.nanosecond,
                value: DiskSpaceUsageView.parse(o.value)
            };
        });
        this.histories = this.histories.concat(histories);
        this.latest = this.histories.length > 0 ? this.histories[this.histories.length - 1] : null;

        const y = d3.scaleBand()
                    .domain(d3.range(this.latest.value.length))
                    .rangeRound([margin.top, height - margin.bottom])
                    .padding(0.1);

        // Y BAR UPDATE
        this.y.call(g =>  g.attr("transform", `translate(${margin.left},0)`)
                           .call(d3.axisLeft(y)
                                   .tickFormat(i => this.latest.value[i].fs)
                                   .tickSizeOuter(0)));
        // REAL BAR UPDATE
        this.chart.attr("fill", "steelblue")
                  .selectAll("rect")
                  .data(this.latest.value)
                  .join("rect")
                    .attr("d", d => parseFloat(d.percent.substring(0, d.percent.length - 1)) / 100)
                    .attr("x", x(0))
                    .attr("y", (d, i) => y(i))
                    .attr("width", d => x(parseFloat(d.percent.substring(0, d.percent.length - 1)) / 100) - x(0))
                    .attr("height", y.bandwidth());

        this.text.attr("fill", "white")
                 .attr("text-anchor", "end")
                 .attr("font-family", "sans-serif")
                 .attr("font-size", 7)
                 .selectAll("text")
                 .data(this.latest.value)
                 .join("text")
                    .attr("x", d => x(parseFloat(d.percent.substring(0, d.percent.length - 1)) / 100))
                    .attr("y", (d, i) => y(i) + y.bandwidth() / 2)
                    .attr("dy", "0.35em")
                    .attr("dx", -4)
                    .text(d => d.mounted + " " + (parseFloat(d.percent.substring(0, d.percent.length - 1)) / 100) + "%" )
                 .call(text => text.filter(d => x(parseFloat(d.percent.substring(0, d.percent.length - 1)) / 100) - x(0) < 5) // short bars
                    .attr("dx", +4)
                    .attr("fill", "black")
                    .attr("text-anchor", "start"));

        this.setState({histories: this.histories, latest: this.latest});
    }

    render() {
        const rows = this.state.latest ? this.state.latest.value.map((o, index) => (<tr key={index}>
            <td>{o.fs}</td>
            <td>{o.size}</td>
            <td>{o.used}</td>
            <td>{o.avail}</td>
            <td>{o.percent}</td>
            <td>{o.mounted}</td>
        </tr>)) : (<tr><td colSpan="6">NO DATA</td></tr>)
        return (
            <div className="card">
                <div className="card-body">
                    Disk Space Usage View
                    <div className="col">
                        <svg ref={node => this.svg = d3.select(node)} viewBox={[ 0, 0, width, height ]}>
                            <g ref={node => this.y = d3.select(node)}></g>
                            <g ref={node => this.chart = d3.select(node)}></g>
                            <g ref={node => this.text = d3.select(node)}></g>
                        </svg>
                    </div>
                    <table className="table">
                        <thead>
                            <tr>
                                <th scope="col">Filesystem</th>
                                <th scope="col">Size</th>
                                <th scope="col">Used</th>
                                <th scope="col">Avail</th>
                                <th scope="col">Used (%)</th>
                                <th scope="col">Mounted on</th>
                            </tr>
                        </thead>
                        <tbody>
                            {rows}
                        </tbody>
                    </table>
                </div>
            </div>
        );
    }
}