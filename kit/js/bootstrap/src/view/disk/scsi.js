/**
 * manpages proc
 * 
 * /proc/scsi/scsi
 * 
 * This is a listing of all scsi devices known to the kernel.
 * this listing is similar to the one seen during bootup.
 * scsi currently supports only the add-single-device command which allows root to add a hotplugged device to the list of known devices.
 * 
 * The command
 *      echo 'scsi add-single-device 1 0 5 0' > /proc/scsi/scsi
 * 
 * will cause host scsi1 to scan on scsi channel 0 for a device on ID 5 LUN 0.
 * If there is already a device known on this address or the address is invalid, an error will be returned.
 * 
 */
import axios from "axios";
import React, { Component } from "react"

export default class DiskScsiView extends Component {
    static parse(history) {
        history.value = history.value.split(/\r?\n/)
                                     .filter((o, index) => index > 0 && o.trim());


        // Attached devices:
        // Host: scsi0 Channel: 00 Id: 00 Lun: 00
        //   Vendor: ATA      Model: KINGSTON RBU-SNS Rev: 01.6
        //   Type:   Direct-Access                    ANSI  SCSI revision: 05
        const devices = [];
        for(let i = 0; i < history.value.length; i = i + 3) {
            const first = history.value[i + 0].split(/[A-Za-z]+:/).map(o => o.trim()).filter(o => o);
            const second = history.value[i + 1].split(/[A-Za-z]+:/).map(o => o.trim()).filter(o => o);
            const third = history.value[i + 2].split(/[A-Za-z]+:/).map(o => o.trim()).filter(o => o);

            devices.push({
                host: first[0],
                channel: first[1],
                id: first[2],
                lun: first[3],
                vender: second[0],
                model: second[1], 
                rev: second[2],
                type: third[0].replace(/\s+/g, " "),
                revision: third[1]
            });
        }

        history.value = devices;

        console.log(history);

        return history;
    }
    constructor(props) {
        super(props);

        this.state = {
            historeis: [],
            latest: null
        };

        this.histories = [];

        this.latest = {
            host: "scsi0",
            channel: "00",
            id: "00",
            lun: "00",
            vender: "ATA",
            model: "KINGSTON RBU-SNS",
            rev: "01.6",
            type: "Direct-Access",
            revision: "05"
        };

        this.onScsi = this.onScsi.bind(this);

        axios.get("http://192.168.0.124:8092/api/disk/scsi", { headers: { "Content-Type": "application/json"}})
             .then(o => {
                 const histories = o.data.map(o => {
                    return DiskScsiView.parse(o);
                 });
                 this.onScsi(histories);
             })
             .catch(e => console.log(e));
    }

    onScsi(histories) {
        this.histories = this.histories.concat(histories);

        if(100 < this.histories.length) {
            this.histories = this.histories.slice(this.histories.length - 100);
        }

        this.latest = this.histories.length > 0 ? this.histories[this.histories.length - 1] : null;


        this.setState({histories: this.histories, latest: this.latest});
    }

    render() {
        console.log(this.latest);
        const rows = this.latest && this.latest.value && this.latest.value.length > 0 ? 
        this.latest.value.map((o, index)=> (
            <tr key={index}>
                <td>{(o.host) || ''}</td>
                <td>{(o.channel) || ''}</td>
                <td>{(o.id) || ''}</td>
                <td>{(o.lun) || ''}</td>
                <td>{(o.vender) || ''}</td>
                <td>{(o.model) || ''}</td>
                <td>{(o.rev) || ''}</td>
                <td>{(o.type) || ''}</td>
                <td>{(o.revision) || ''}</td>
            </tr>
        ))
        : (<tr><td colSpan="9">NO DATA</td></tr>)
        return (
            <div className="row">
                <div className="card">
                    <div className="card-body">
                        <table className="table">
                            <thead>
                                <tr>
                                    <th scope="row">Host</th>
                                    <th scope="row">Channel</th>
                                    <th scope="row">ID</th>
                                    <th scope="row">LUN</th>
                                    <th scope="row">Vendor</th>
                                    <th scope="row">Model</th>
                                    <th scope="row">Rev</th>
                                    <th scope="row">Type</th>
                                    <th scope="row">Revision</th>
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