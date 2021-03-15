import axios from "axios";
import React, { Component } from "react";

export default class MemInfoView extends Component {
    static parse(history) {
        if(history) {
            const lines = history.value.split(/\r?\n/);
            const result = {
                total: null,
                free: null,
                avail: null,
                buffers: null,
                cached: null,
                active: null,
                inactive: null,
                anon: {
                    active: null,
                    inactive: null,
                    pages: null
                },
                file: {
                    active: null,
                    inactive: null
                },
                unevictable: null,
                mlocked: null,
                swap: {
                    cached: null,
                    total: null,
                    free: null,
                },
                dirty: null,
                writeback: null,
                mapped: null,
                shmem: null,
                kreclaimable: null,
                slab: null,
                sreclaimable: null,
                sunreclaim: null,
                kernelstack: null,
                pagetables: null,
                nfsunstables: null,
                bounce: null,
                writebacktmp: null,
                commitlimit: null,
                committedas: null,
                vmalloc: {
                    total: null,
                    used: null,
                    chunk: null,
                },
                percpu: null,
                hardwarecorrupted: null,
                anonhugepages: null,
                shmemhugepages: null,
                shmempmdmapped: null,
                filehugepages: null,
                filepmdmapped: null,
                hugepagestotal: null,
                hugepagesfree: null,
                hugepagesrsvd: null,
                hugepagessurp: null,
                hugepagesize: null,
                hugetlb: null,
                directmap4k: null,
                directmap2m: null,
                directmap1g: null
            };

            for(let i = 0; i < lines.length; i++) {
                if(lines[i].startsWith("MemTotal:")) {
                    result.total = lines[i].substring("MemTotal:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("MemFree:")) {
                    result.free = lines[i].substring("MemFree:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("MemAvailable:")) {
                    result.avail = lines[i].substring("MemAvailable:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Buffers:")) {
                    result.buffers = lines[i].substring("Buffers:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Cached:")) {
                    result.cached = lines[i].substring("Cached:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("SwapCached:")) {
                    result.swap.cached = lines[i].substring("SwapCached:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Active:")) {
                    result.active = lines[i].substring("Active:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Inactive:")) {
                    result.inactive = lines[i].substring("Inactive:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Active(anon):")) {
                    result.anon.active = lines[i].substring("Active(anon):".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Inactive(anon):")) {
                    result.anon.inactive = lines[i].substring("Inactive(anon):".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Active(file):")) {
                    result.file.active = lines[i].substring("Active(file):".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Inactive(file):")) {
                    result.file.inactive = lines[i].substring("Inactive(file):".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Unevictable:")) {
                    result.unevictable = lines[i].substring("Unevictable:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Mlocked:")) {
                    result.mlocked = lines[i].substring("Mlocked:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("SwapTotal:")) {
                    result.swap.total = lines[i].substring("SwapTotal:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("SwapFree:")) {
                    result.swap.free = lines[i].substring("SwapFree:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Dirty:")) {
                    result.dirty = lines[i].substring("Dirty:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Writeback:")) {
                    result.writeback = lines[i].substring("Writeback:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("AnonPages:")) {
                    result.anon.pages = lines[i].substring("AnonPages:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Mapped:")) {
                    result.mapped = lines[i].substring("Mapped:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Shmem:")) {
                    result.shmem = lines[i].substring("Shmem:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("KReclaimable:")) {
                    result.kreclaimable = lines[i].substring("KReclaimable:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Slab:")) {
                    result.slab = lines[i].substring("Slab:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("SReclaimable:")) {
                    result.sreclaimable = lines[i].substring("SReclaimable:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("SUnreclaim:")) {
                    result.sunreclaim = lines[i].substring("SUnreclaim:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("KernelStack:")) {
                    result.kernelstack = lines[i].substring("KernelStack:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("PageTables:")) {
                    result.pagetables = lines[i].substring("PageTables:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("NFS_Unstable:")) {
                    result.nfsunstables = lines[i].substring("NFS_Unstable:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Bounce:")) {
                    result.bounce = lines[i].substring("Bounce:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("WritebackTmp:")) {
                    result.writebacktmp = lines[i].substring("WritebackTmp:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("CommitLimit:")) {
                    result.commitlimit = lines[i].substring("CommitLimit:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Committed_AS:")) {
                    result.committedas = lines[i].substring("Committed_AS:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("VmallocTotal:")) {
                    result.vmalloc.total = lines[i].substring("VmallocTotal:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("VmallocUsed:")) {
                    result.vmalloc.used = lines[i].substring("VmallocUsed:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("VmallocChunk:")) {
                    result.vmalloc.chunk = lines[i].substring("VmallocChunk:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Percpu:")) {
                    result.percpu = lines[i].substring("Percpu:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("HardwareCorrupted:")) {
                    result.hardwarecorrupted = lines[i].substring("HardwareCorrupted:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("AnonHugePages:")) {
                    result.anonhugepages = lines[i].substring("AnonHugePages:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("ShmemHugePages:")) {
                    result.shmemhugepages = lines[i].substring("ShmemHugePages:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("ShmemPmdMapped:")) {
                    result.shmempmdmapped = lines[i].substring("ShmemPmdMapped:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("FileHugePages:")) {
                    result.filehugepages = lines[i].substring("FileHugePages:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("FilePmdMapped:")) {
                    result.filepmdmapped = lines[i].substring("FilePmdMapped:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("HugePages_Total:")) {
                    result.hugepagestotal = lines[i].substring("HugePages_Total:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("HugePages_Free:")) {
                    result.hugepagesfree = lines[i].substring("HugePages_Free:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("HugePages_Rsvd:")) {
                    result.hugepagesrsvd = lines[i].substring("HugePages_Rsvd:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("HugePages_Surp:")) {
                    result.hugepagessurp = lines[i].substring("HugePages_Surp:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Hugepagesize:")) {
                    result.hugepagesize = lines[i].substring("Hugepagesize:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("Hugetlb:")) {
                    result.hugetlb = lines[i].substring("Hugetlb:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("DirectMap4k:")) {
                    result.directmap4k = lines[i].substring("DirectMap4k:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("DirectMap2M:")) {
                    result.directmap2m = lines[i].substring("DirectMap2M:".length).trim();
                    continue;
                }
                if(lines[i].startsWith("DirectMap1G:")) {
                    result.directmap1g = lines[i].substring("DirectMap1G:".length).trim();
                    continue;
                }
            }
            history.value = result;
        }
        
        return history;
    }
    constructor(props) {
        super(props);

        this.state = {
            histories: [],
            latest: null
        };

        this.latest = null;
        this.histories = [];

        this.onMemInfo = this.onMemInfo.bind(this);

        axios.get("http://192.168.0.124:8092/api/mem/info", { headers: { "Content-Type": "application/json" }})
             .then(o => this.onMemInfo(o.data))
             .catch(e => console.log(e));


    }

    onMemInfo(histories) {
        histories = histories.map(o => MemInfoView.parse(o));

        this.histories = this.histories.concat(histories);
        if(100 < this.histories.length)
        {
            this.histories = this.histories.slice(this.histories.length - 1);
        }
        this.latest = this.histories.length > 0 ? this.histories[this.histories.length - 1] : null;

        this.setState({
            histories: this.histories,
            latest: this.latest
        });
    }

    render() {
        return (
            <div className="row">
                <div className="card">
                    <div className="card-body">
                        MEM INFO
                        <table className="table">
                            <tbody>
                                <tr><th scope="col">Total</th><td>{(this.latest && this.latest.value) ? this.latest.value.total : "-"}</td></tr>
                                <tr><th scope="col">Free</th><td>{(this.latest && this.latest.value) ? this.latest.value.free : "-"}</td></tr>
                                <tr><th scope="col">Available</th><td>{(this.latest && this.latest.value) ? this.latest.value.avail : "-"}</td></tr>
                                <tr><th scope="col">Buffers</th><td>{(this.latest && this.latest.value) ? this.latest.value.buffers : "-"}</td></tr>
                                <tr><th scope="col">cached</th><td>{(this.latest && this.latest.value) ? this.latest.value.cached : "-"}</td></tr>
                                <tr><th scope="col">Swap cached</th><td>{(this.latest && this.latest.value) ? this.latest.value.swap.cached : "-"}</td></tr>
                                <tr><th scope="col">Active</th><td>{(this.latest && this.latest.value) ? this.latest.value.active : "-"}</td></tr>
                                <tr><th scope="col">Inactive</th><td>{(this.latest && this.latest.value) ? this.latest.value.inactive : "-"}</td></tr>
                                <tr><th scope="col">Active (anon)</th><td>{(this.latest && this.latest.value) ? this.latest.value.anon.active : "-"}</td></tr>
                                <tr><th scope="col">Inactive (anon)</th><td>{(this.latest && this.latest.value) ? this.latest.value.anon.inactive : "-"}</td></tr>
                                <tr><th scope="col">Active (anon)</th><td>{(this.latest && this.latest.value) ? this.latest.value.file.active : "-"}</td></tr>
                                <tr><th scope="col">Inactive (anon)</th><td>{(this.latest && this.latest.value) ? this.latest.value.file.inactive : "-"}</td></tr>
                                <tr><th scope="col">Unevictable</th><td>{(this.latest && this.latest.value) ? this.latest.value.unevictable : "-"}</td></tr>
                                <tr><th scope="col">Mlocked</th><td>{(this.latest && this.latest.value) ? this.latest.value.mlocked : "-"}</td></tr>
                                <tr><th scope="col">Swap total</th><td>{(this.latest && this.latest.value) ? this.latest.value.swap.total : "-"}</td></tr>
                                <tr><th scope="col">Swap free</th><td>{(this.latest && this.latest.value) ? this.latest.value.swap.free : "-"}</td></tr>
                                <tr><th scope="col">Dirty</th><td>{(this.latest && this.latest.value) ? this.latest.value.dirty : "-"}</td></tr>
                                <tr><th scope="col">Writeback</th><td>{(this.latest && this.latest.value) ? this.latest.value.writeback : "-"}</td></tr>
                                <tr><th scope="col">Anon Pages</th><td>{(this.latest && this.latest.value) ? this.latest.value.anon.pages : "-"}</td></tr>
                                <tr><th scope="col">Mapped</th><td>{(this.latest && this.latest.value) ? this.latest.value.mapped : "-"}</td></tr>
                                <tr><th scope="col">Shmem</th><td>{(this.latest && this.latest.value) ? this.latest.value.shmem : "-"}</td></tr>
                                <tr><th scope="col">KReclaimable</th><td>{(this.latest && this.latest.value) ? this.latest.value.kreclaimable : "-"}</td></tr>
                                <tr><th scope="col">Slab</th><td>{(this.latest && this.latest.value) ? this.latest.value.slab : "-"}</td></tr>
                                <tr><th scope="col">SReclaimable</th><td>{(this.latest && this.latest.value) ? this.latest.value.sreclaimable : "-"}</td></tr>
                                <tr><th scope="col">SUnreclaim</th><td>{(this.latest && this.latest.value) ? this.latest.value.sunreclaim : "-"}</td></tr>
                                <tr><th scope="col">Kernel Stack</th><td>{(this.latest && this.latest.value) ? this.latest.value.kernelstack : "-"}</td></tr>
                                <tr><th scope="col">Page Tables</th><td>{(this.latest && this.latest.value) ? this.latest.value.pagetables : "-"}</td></tr>
                                <tr><th scope="col">NFS Unstables</th><td>{(this.latest && this.latest.value) ? this.latest.value.nfsunstables : "-"}</td></tr>
                                <tr><th scope="col">Bounce</th><td>{(this.latest && this.latest.value) ? this.latest.value.bounce : "-"}</td></tr>
                                <tr><th scope="col">WritebackTmp</th><td>{(this.latest && this.latest.value) ? this.latest.value.writebacktmp : "-"}</td></tr>
                                <tr><th scope="col">Commit Limit</th><td>{(this.latest && this.latest.value) ? this.latest.value.commitlimit : "-"}</td></tr>
                                <tr><th scope="col">Committed AS</th><td>{(this.latest && this.latest.value) ? this.latest.value.committedas : "-"}</td></tr>
                                <tr><th scope="col">Vmalloc Total</th><td>{(this.latest && this.latest.value) ? this.latest.value.vmalloc.total : "-"}</td></tr>
                                <tr><th scope="col">Vmalloc Used</th><td>{(this.latest && this.latest.value) ? this.latest.value.vmalloc.used : "-"}</td></tr>
                                <tr><th scope="col">Vmalloc Chunk</th><td>{(this.latest && this.latest.value) ? this.latest.value.vmalloc.chunk : "-"}</td></tr>
                                <tr><th scope="col">Per cpu</th><td>{(this.latest && this.latest.value) ? this.latest.value.percpu : "-"}</td></tr>
                                <tr><th scope="col">Hardware Corrupted</th><td>{(this.latest && this.latest.value) ? this.latest.value.hardwarecorrupted : "-"}</td></tr>
                                <tr><th scope="col">Anon Huge Pages</th><td>{(this.latest && this.latest.value) ? this.latest.value.anonhugepages : "-"}</td></tr>
                                <tr><th scope="col">Shmem Huge Pages</th><td>{(this.latest && this.latest.value) ? this.latest.value.shmemhugepages : "-"}</td></tr>
                                <tr><th scope="col">Shmem Pmd Mapped</th><td>{(this.latest && this.latest.value) ? this.latest.value.shmempmdmapped : "-"}</td></tr>
                                <tr><th scope="col">File Huge Pages</th><td>{(this.latest && this.latest.value) ? this.latest.value.filehugepages : "-"}</td></tr>
                                <tr><th scope="col">File Pmd Mapped</th><td>{(this.latest && this.latest.value) ? this.latest.value.filepmdmapped : "-"}</td></tr>
                                <tr><th scope="col">Huge Pages Total</th><td>{(this.latest && this.latest.value) ? this.latest.value.hugepagestotal : "-"}</td></tr>
                                <tr><th scope="col">Huge Pages Free</th><td>{(this.latest && this.latest.value) ? this.latest.value.hugepagesfree : "-"}</td></tr>
                                <tr><th scope="col">Huge Pages Rsvd</th><td>{(this.latest && this.latest.value) ? this.latest.value.hugepagesrsvd : "-"}</td></tr>
                                <tr><th scope="col">Huge Pages Surp</th><td>{(this.latest && this.latest.value) ? this.latest.value.hugepagessurp : "-"}</td></tr>
                                <tr><th scope="col">Huge page size</th><td>{(this.latest && this.latest.value) ? this.latest.value.hugepagesize : "-"}</td></tr>
                                <tr><th scope="col">Hugetlb</th><td>{(this.latest && this.latest.value) ? this.latest.value.hugetlb : "-"}</td></tr>
                                <tr><th scope="col">DirectMap4k</th><td>{(this.latest && this.latest.value) ? this.latest.value.directmap4k : "-"}</td></tr>
                                <tr><th scope="col">DirectMap2M</th><td>{(this.latest && this.latest.value) ? this.latest.value.directmap2m : "-"}</td></tr>
                                <tr><th scope="col">DirectMap1G</th><td>{(this.latest && this.latest.value) ? this.latest.value.directmap1g : "-"}</td></tr>
                            </tbody>
                        </table>
                    </div>
                </div>
            </div>
        );
    }
}