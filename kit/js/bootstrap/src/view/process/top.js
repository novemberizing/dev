/**
 * 
 */

import React, { Component } from "react";
import * as d3 from "d3";
import axios from "axios";

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
            .domain([0, 100])
            .range([height- margin.bottom, margin.top]);

export default class ProcessTopView extends Component {
    static first(line) {
        const first = line.slice(line.indexOf("-") + 1).trim();
        const strings = first.split(/\s+/);

        return {
            time: strings[0],
            duration: strings[2].slice(0, strings[2].length - 1),
            user: strings[3],
            load: [
                strings[7].slice(0, strings[7].length - 1),
                strings[8].slice(0, strings[8].length - 1),
                strings[9]
            ]
        };
    }
    static second(line) {
        const second = line.slice(line.indexOf(":") + 1).trim();
        const strings = second.split(/\s+/);

        return {
            total: parseInt(strings[0]),
            running: parseInt(strings[2]),
            sleeping: parseInt(strings[4]),
            stopped: parseInt(strings[6]),
            zombie: parseInt(strings[8])
        };
    }

    static third(line) {
        const second = line.slice(line.indexOf(":") + 1).trim();
        const strings = second.split(/\s+/);

        return {
            user: parseFloat(strings[0]),
            system: parseFloat(strings[2]),
            nice: parseFloat(strings[4]),
            idle: parseFloat(strings[6]),
            wait: parseFloat(strings[8]),
            interrupt: {
                hard: parseFloat(strings[10]),
                soft: parseFloat(strings[12]),
            },
            steal: parseFloat(strings[14])
        };
    }

    static fourth(line) {
        const second = line.slice(line.indexOf(":") + 1).trim();
        const strings = second.split(/\s+/);

        return {
            total: strings[0],
            free: strings[2],
            used: strings[4],
            cache: strings[6]
        };
    }

    static fifth(line) {
        const second = line.slice(line.indexOf(":") + 1).trim();
        const strings = second.split(/\s+/);

        return {
            total: strings[0],
            free: strings[2],
            used: strings[4],
            cache: strings[6]
        };
    }

    static processes(lines) {
        return lines.map(o => o.trim().split(/\s+/))
                    .map(o => o.slice(0, 11).concat(o.slice(11).join(" ")));
    }

    static parse(json) {
        const lines = json.data.split(/\r?\n/);

        const { time, duration, user, load } = ProcessTopView.first(lines[0]);
        const tasks = ProcessTopView.second(lines[1]);
        const cpu = ProcessTopView.third(lines[2]);
        const mem = ProcessTopView.fourth(lines[3]);
        const swap = ProcessTopView.fifth(lines[4]);
        const processes = ProcessTopView.processes(lines.slice(7));

        return { time, duration, user, load, tasks, cpu, mem, swap, processes };
    }

    constructor(props) {
        super(props);

        this.state = {
            histories: [],
            latest: null
        };

        this.histories = [];

        this.width = width;
        this.height = height;

        this.interval = setInterval(() => {
            axios.get("http://192.168.0.124:8092/api/top", { headers: { "Content-Type": "application/json" } })
                 .then(o => this.onTop(o.data))
                 .catch(e => console.log(e));

        }, 1000);
    }

    componentDidMount() {



        this.svg.append("g").call(g => g.attr("transform", `translate(0, ${this.height - margin.bottom})`)
                                        .call(d3.axisBottom()
                                                .scale(x)));

        this.svg.append("g").call(g => g.attr("transform", `translate(${margin.left}, 0)`)
                                        .call(d3.axisLeft()
                                                .scale(y)));

    }

    componentWillUnmount() {

    }

    onTop(data) {
        this.histories.push(ProcessTopView.parse(data));

        if(100 < this.histories.length) {
            this.histories = this.histories.slice(this.histories.length - 100);
        }

        const latest = this.histories[this.histories.length - 1];

        const series = this.histories.map(o => {
            return o.cpu.user + o.cpu.system
        });

        // console.log(series.length);
        // console.log(this.node.selectAll("path"));

        this.node.datum(series)
                .attr("fill", "none")
                .attr("stroke", "steelblue")
                .attr("stroke-width", 1.5)
                .attr("stroke-linejoin", "round")
                .attr("stroke-linecap", "round")
                .attr("d", d3.line()
                             .x((d, index) => x(index))
                             .y((d, index) => y(d)));

        this.setState({histories: this.histories, latest});
    }
 
    render() {
        const histories = this.state.histories;
        const latest = this.state.latest;

        const rows = latest && latest.processes && latest.processes.length > 0 ? latest.processes.map((o, index) => (
            <tr key={index}>
                <td>{o[0]}</td>
                <td>{o[1]}</td>
                <td>{o[2]}</td>
                <td>{o[3]}</td>
                <td>{o[4]}</td>
                <td>{o[5]}</td>
                <td>{o[6]}</td>
                <td>{o[7]}</td>
                <td>{o[8]}</td>
                <td>{o[9]}</td>
                <td>{o[10]}</td>
                <td>{o[11]}</td>
            </tr>
        )) : (<tr><td colSpan="12">no data</td></tr>)
     
        return (
            <div className="card">
                <div className="card-body">
                   {/** CURRENT PROCESS SUMMARY */}
                    <table className="table">
                        <tbody>
                            <tr>
                                <th scope="row">
                                   TIME
                                </th>
                                <td>
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.time : 0} / UP {latest ? latest.duration : 0}
                                    </span>
                                    <span className="badge badge-light text-dark ms-1">
                                        {latest ? latest.user : 0} <sub className="text-gray">users</sub>
                                    </span>
                                </td>
                                <th scope="row">
                                    LOAD AVERAGE
                                </th>
                                <td>
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.load[0] : 0.0} <sub className="text-gray">1m</sub>
                                    </span>
                                    <span className="badge badge-light text-dark mx-1">
                                        {latest ? latest.load[1] : 0.0} <sub className="text-gray">5m</sub>
                                    </span>
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.load[2] : 0.0} <sub className="text-gray">15m</sub>
                                    </span>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">TASKS</th>
                                <td colSpan="3">
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.tasks.total : 0} <sub className="text-gray">total</sub>
                                    </span>
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.tasks.running : 0} <sub className="text-gray">running</sub>
                                    </span>
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.tasks.sleeping : 0} <sub className="text-gray">sleeping</sub>
                                    </span>
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.tasks.stopped : 0} <sub className="text-gray">stopped</sub>
                                    </span>
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.tasks.zombie : 0} <sub className="text-gray">zombie</sub>
                                    </span>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">CPU</th>
                                <td colSpan="3">
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.cpu.user : 0.0} <sub className="text-gray">user</sub>
                                    </span>
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.cpu.system : 0.0} <sub className="text-gray">system</sub>
                                    </span>
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.cpu.nice : 0.0} <sub className="text-gray">nice</sub>
                                    </span>
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.cpu.idle : 0.0} <sub className="text-gray">idle</sub>
                                    </span>
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.cpu.wait : 0.0} <sub className="text-gray">wait</sub>
                                    </span>
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.cpu.interrupt.hard : 0.0} <sub className="text-gray">hard</sub>
                                    </span>
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.cpu.interrupt.soft : 0.0} <sub className="text-gray">soft</sub>
                                    </span>
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.cpu.steal : 0.0} <sub className="text-gray">steal</sub>
                                    </span>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    MEM <sub>MiB</sub>
                                </th>
                                <td colSpan="3">
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.mem.total : 0} <sub className="text-gray">total</sub>
                                    </span>
                                    <span className="badge badge-light text-dark ms-1">
                                        {latest ? latest.mem.free : 0} <sub className="text-gray">free</sub>
                                    </span>
                                    <span className="badge badge-light text-dark ms-1">
                                        {latest ? latest.mem.used : 0} <sub className="text-gray">used</sub>
                                    </span>
                                    <span className="badge badge-light text-dark ms-1">
                                        {latest ? latest.mem.cache : 0} <sub className="text-gray">cache</sub>
                                    </span>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    SWAP <sub>MiB</sub>
                                </th>
                                <td colSpan="3">
                                    <span className="badge badge-light text-dark">
                                        {latest ? latest.swap.total : 0} <sub className="text-gray">total</sub>
                                    </span>
                                    <span className="badge badge-light text-dark ms-1">
                                        {latest ? latest.swap.free : 0} <sub className="text-gray">free</sub>
                                    </span>
                                    <span className="badge badge-light text-dark ms-1">
                                        {latest ? latest.swap.used : 0} <sub className="text-gray">used</sub>
                                    </span>
                                    <span className="badge badge-light text-dark ms-1">
                                        {latest ? latest.swap.cache : 0} <sub className="text-gray">cache</sub>
                                    </span>
                                </td>
                            </tr>
                        </tbody>
                    </table>
                    {/** PROCESS CPU/MEMORY GRAPH */}
                    <div className="col">
                        <svg ref={node => this.svg = d3.select(node)} viewBox={[ 0, 0, this.width, this.height ]}>
                            <path ref={node => this.node = d3.select(node)} />
                        </svg>

                    </div>
                    {/** PROCESS DATA TABLE */}
                    <table className="table">
                        <thead>
                            <tr>
                                <th scope="col">PID</th>
                                <th scope="col">USER</th>
                                <th scope="col">PRIORITY</th>
                                <th scope="col">NICE</th>
                                <th scope="col">VIRTUAL</th>
                                <th scope="col">RESIDENT</th>
                                <th scope="col">SHARED</th>
                                <th scope="col">STATUS</th>
                                <th scope="col">CPU</th>
                                <th scope="col">MEM</th>
                                <th scope="col">TIME+</th>
                                <th scope="col">COMMAND</th>
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