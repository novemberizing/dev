import React, { Component } from "react";
import axios from "axios";
import * as d3 from "d3";

const width = 800;
const height = 200;

const margin = {
    top: 10,
    bottom: 20,
    left: 25,
    right: 10
};

const x = d3.scaleLinear()
            .domain([0, 100])
            .range([margin.left, width - margin.right]);

const y = d3.scaleLinear()
            .domain([0, 1000])
            .range([height- margin.bottom, margin.top]);

const line = d3.line()
               .x((d, i) => {
                   return x(i);
               })
               .y((d, i) => {
                   return y(d);
               });

// TODO: 여러 파일 시스템에 대한 그래프를 그려야 한다.
// 하나 이상의 것을 그릴 수 있도록 하자.
export default class DiskStatView extends Component {
    static parse(history) {
        const result = {
            machine: null,
            date: null,
            arch: null,
            cpu: {
                total: null,
                user: null,
                nice: null,
                system: null,
                wait: null,
                steal: null,
                idle: null
            },
            devices: []
        };
        const lines = history.value.split(/\r?\n/);
        {
            const strings = lines[0].split(/\t/);
            result.machine = strings[0].trim();
            result.date = strings[1].trim();
            result.arch = strings[2].trim();
            result.cpu.total = strings[3].trim();
        }
        
        {
            const strings = lines[3].split(/\s+/);
            result.cpu.user = strings[1];
            result.cpu.nice = strings[2];
            result.cpu.system = strings[3];
            result.cpu.wait = strings[4];
            result.cpu.steal = strings[5];
            result.cpu.idle = strings[6];
        }

        {
            for(let i = 6; i < lines.length; i++)
            {
                if(lines[i].trim())
                {
                    const strings = lines[i].split(/\s+/);
                    result.devices.push({
                        device: strings[0],
                        tps: strings[1],
                        readpersec: strings[2],
                        writepersec: strings[3],
                        discardedpersec: strings[4],
                        read: strings[5],
                        write: strings[6],
                        discarded: strings[7]
                    });
                }
            }
        }

        history.value = result;

        return history;
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
        this.node = null;

        this.onStat = this.onStat.bind(this);

        this.interval = setInterval(() => {
            axios.get("http://192.168.0.124:8092/api/disk/stat", { headers: { "Content-Type": "application/json" } })
                 .then(o => this.onStat(o.data))
                 .catch(e => console.log(e));

        }, 1000);

        // axios.get("http://192.168.0.124:8092/api/disk/stat", { headers: { "Content-Type": "application/json" }})
        //      .then(o => this.onStat(o.data))
        //      .catch(e => console.log(e));
    }

    onStat(histories) {
        histories = histories.map(o => DiskStatView.parse(o));

        this.histories = this.histories.concat(histories);
        this.latest = this.histories.length > 0 ? this.histories[this.histories.length - 1] : null;

        this.readpersecs = [];
        this.data = []
        this.data.push(this.histories.map((o, index) => parseFloat(o.value.devices[0].tps)));
        this.data.push(this.histories.map((o, index) => parseFloat(o.value.devices[0].readpersec)));
        this.data.push(this.histories.map((o, index) => parseFloat(o.value.devices[0].writepersec)));
        this.data.push(this.histories.map((o, index) => parseFloat(o.value.devices[0].discardedpersec)));

        if(this.histories.length > 100)
        {
            this.histories = this.histories.slice(this.histories.length - 100);
        }
        // device

        // console.log(this.histories.length);
        this.node.attr("fill", "none")
                 .attr("stroke-width", 1.5)
                 .attr("stroke-linejoin", "round")
                 .attr("stroke-linecap", "round")
                 .selectAll("path")
                    .data(this.data)
                    .join("path")
                        .attr("stroke", (d, i) => {
                            return ["#aaa", "green", "blue", "red"][i];
                        })
                        .attr("d", (d, index) => {
                            return line(d, index);
                        });

        this.setState({
            histories: this.histories,
            latest: this.latest
        });
    }

    componentDidMount() {
        this.svg.append("g").call(g => g.attr("transform", `translate(0, ${height - margin.bottom})`)
                                        .call(d3.axisBottom()
                                                .scale(x)));

        this.svg.append("g").call(g => g.attr("transform", `translate(${margin.left}, 0)`)
                                        .call(d3.axisLeft()
                                                .scale(y)));

    }

    render() {

        const latest = this.latest;
        const rows = this.latest && this.latest.value && this.latest.value.devices && this.latest.value.devices.length > 0 ?
            this.latest.value.devices.map((o, index) => (
                <tr key={index}>
                    <td>{o.device}</td>
                    <td>{o.tps}</td>
                    <td>{o.readpersec}</td>
                    <td>{o.writepersec}</td>
                    <td>{o.discardedpersec}</td>
                    <td>{o.read}</td>
                    <td>{o.write}</td>
                    <td>{o.discarded}</td>
                </tr>
            ))
            : <tr><td colSpan="8">no data</td></tr>

        // const rows = 
        
        return (
            <div className="row">
                <div className="card">
                    <div className="card-body">
                        IO STAT

                        <table className="table">
                            <tbody>
                                <tr>
                                    <th scope="col">{this.latest && this.latest.value && (this.latest.value.machine || '-')}</th>
                                    <th scope="col">{this.latest && this.latest.value && (this.latest.value.date || '-')}</th>
                                    <th scope="col">{this.latest && this.latest.value && (this.latest.value.arch || '-')}</th>
                                    <th scope="col">{this.latest && this.latest.value && (this.latest.value.cpu.total || '-')}</th>
                                </tr>
                            </tbody>
                        </table>

                        <table className="table">
                            <thead>
                                <tr>
                                    <th scope="row">CPU</th>
                                    <th scope="row">USER</th>
                                    <th scope="row">NICE</th>
                                    <th scope="row">SYSTEM</th>
                                    <th scope="row">WAIT</th>
                                    <th scope="row">STEAL</th>
                                    <th scope="row">IDLE</th>
                                </tr>
                            </thead>
                            <tbody>
                                <tr>
                                    <td>Average</td>
                                    <td>{this.latest && this.latest.value && this.latest.value.cpu.user ? `${this.latest.value.cpu.user}%` : '-'}</td>
                                    <td>{this.latest && this.latest.value && this.latest.value.cpu.nice ? `${this.latest.value.cpu.nice}%` : '-'}</td>
                                    <td>{this.latest && this.latest.value && this.latest.value.cpu.system ? `${this.latest.value.cpu.system}%` : '-'}</td>
                                    <td>{this.latest && this.latest.value && this.latest.value.cpu.wait ? `${this.latest.value.cpu.wait}%` : '-'}</td>
                                    <td>{this.latest && this.latest.value && this.latest.value.cpu.steal ? `${this.latest.value.cpu.steal}%` : '-'}</td>
                                    <td>{this.latest && this.latest.value && this.latest.value.cpu.idle ? `${this.latest.value.cpu.idle}%` : '-'}</td>
                                </tr>
                            </tbody>
                        </table>

                        <div className="row">
                            <svg ref={node => this.svg = d3.select(node)} viewBox={[ 0, 0, width, height ]}>
                                <g ref={node => this.node = d3.select(node)} />
                            </svg>
                        </div>

                        <table className="table">
                            <thead>
                                <tr>
                                    <th scope="row">Device</th>
                                    <th scope="row">tps</th>
                                    <th scope="row">KB (read/s)</th>
                                    <th scope="row">KB (write/s)</th>
                                    <th scope="row">KB (discarded/s)</th>
                                    <th scope="row">KB (read)</th>
                                    <th scope="row">KB (write)</th>
                                    <th scope="row">KB (discarded)</th>
                                </tr>
                            </thead>
                            <tbody>
                                {rows}
                            </tbody>
                        </table>
                    </div>
                </div>
            </div>
        );
    }
}