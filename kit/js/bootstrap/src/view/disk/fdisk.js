import React, { Component } from "react";
import axios from "axios";

export default class FDiskListView extends Component {
    static parse(o) {
        const strings = o.split(/\r?\n/);
        const ret = [];
        for(let i = 0; i < strings.length; i++)
        {
            const result = {
                path: null,
                mib: null,
                bytes: null,
                sectors: null,
                units: null,
                size: {
                    sector: null,
                    io: null
                },
                disk: {
                    model: null,
                    label: null,
                    identifier: null
                },
                device: null
            };
            if(strings[i + 0].startsWith("Disk /"))
            {
                result.path = strings[i + 0].substring(5, strings[i + 0].indexOf(":"));
                const array = strings[i + 0].substring(result.path.length + 7).split(/ [a-zA-Z]+,?/);
                result.mib = array[0].trim();
                result.bytes = array[1].trim();
                result.sectors = array[2].trim();
                while(strings[i + 1].trim())
                {
                    const str = strings[i + 1].trim();

                    if(str.startsWith("Units:")) {
                        result.units = str.substring(7).trim();
                    }
                    if(str.startsWith("Sector size (logical/physical):")) {
                        result.size.sector = str.substring("Sector size (logical/physical):".length).trim();
                    }
                    if(str.startsWith("I/O size (minimum/optimal):")) {
                        result.size.io = str.substring("I/O size (minimum/optimal):".length).trim();
                    }
                    if(str.startsWith("Disk model:")) {
                        result.disk.model = str.substring("Disk model:".length).trim();
                    }
                    if(str.startsWith("Disklabel type:")) {
                        result.disk.label = str.substring("Disklabel type:".length).trim();
                    }
                    if(str.startsWith("Disk identifier:")) {
                        result.disk.identifier = str.substring("Disk identifier:".length).trim();
                    }
                    
                    i = i + 1;
                    if(i + 2 < strings.length)
                    {
                        if(strings[i + 2].trim().startsWith("Device")) {
                            i = i + 3;
                            result.device = [];
                            while(strings[i].trim()) {
                                const str = strings[i].split(/\s+/);
                                
                                result.device.push({
                                    device: str[0],
                                    boot: str[1] === '*' ? str[1] : "",
                                    start: str[1] === '*' ? str[2] : str[1],
                                    end: str[1] === '*' ? str[3] : str[2],
                                    sectors: str[1] === '*' ? str[4] : str[3],
                                    size: str[1] === '*' ? str[5] : str[4],
                                    id: str[1] === '*' ? str[6] : str[5],
                                    type: str[1] === '*' ? str.slice(7).join(" ") : str.slice(6).join(" ")
                                });
                                i = i + 1;
                            }
                        }
                    }
                }
                ret.push(result);
            }
        }
        return ret;
    }
    constructor(props) {
        super(props);

        this.state = {
            histories: []
        };

        this.onFDisk = this.onFDisk.bind(this);

        axios.get("http://192.168.0.124:8092/api/disk/fdisk", { headers: { "Content-Type": "application/json" }})
             .then(o => this.onFDisk(o.data))
             .catch(e => console.log(e));
    }

    onFDisk(histories) {
        // console.log(histories); // 
        // PARSE
        
        histories = histories.map(o => {
            o.value = FDiskListView.parse(o.value);
            return o;
        });

        this.setState({ histories });
    }

    render() {
        // TODO: DEVICES TABLE
        const rows = this.state.histories.length > 0 && this.state.histories[0].value && this.state.histories[0].value.length ? 
              this.state.histories[0].value.map((o, index) => (<tr key={index}>
                          <td>{o.path || '-'}</td>
                          <td>{o.mib || '-'}</td>
                          <td>{o.bytes || '-'}</td>
                          <td>{o.sectors || '-'}</td>
                          <td>{o.units || '-'}</td>
                          <td>{o.size.sector || '-'}</td>
                          <td>{o.size.io || '-'}</td>
                          <td>{o.disk.model || '-'}</td>
                          <td>{o.disk.label || '-'}</td>
                          <td>{o.disk.identifier || '-'}</td>
                          <td>{"-"}</td>
                      </tr>))
            : (<tr><td colSpan="11">no data</td></tr>);
        return (
            <div className="row">
                <div className="card">
                    <div className="card-body">
                        FDISK LIST VIEW
                        <table className="table">
                            <thead>
                                <tr>
                                    <th scope="row">Path</th>
                                    <th scope="row">MiB</th>
                                    <th scope="row">Bytes</th>
                                    <th scope="row">Sectors</th>
                                    <th scope="row">Units</th>
                                    <th scope="row">Sector size</th>
                                    <th scope="row">I/O size</th>
                                    <th scope="row">Disk model</th>
                                    <th scope="row">Disk label type</th>
                                    <th scope="row">identifier</th>
                                    <th scope="row">Devices</th>
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