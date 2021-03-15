import express from "express";
import cors from "cors";
import moment from "moment";
import { exec, execSync as execute } from "child_process";

const password = "qkrwldb@17";

const app = express();
app.use(cors());

const port = 8092;

app.get("/", (req, res) => {
    res.send("Hello World!");
});

app.get("/api/top", (req, res) => {
    const buffer = execute("top -b -n1");
    const result = buffer.toString();

    res.json({data: result});
});

app.get("/api/disk/space/usage", (req, res) => {
    const result = execute(`echo ${password} | sudo -S df -h`);
    const current = new Date();
    const millisecond = current.getTime();

    res.json([{value: result.toString(), clock: parseInt(millisecond/1000), nanosecond: (millisecond % 1000) * 1000000}]);
});

app.get("/api/disk/scsi", (req, res) => {
    const result = execute(`echo ${password} | sudo -S cat /proc/scsi/scsi`);

    const current = new Date();
    const millisecond = current.getTime();

    res.json([{value: result.toString(), clock: parseInt(millisecond/1000), nanosecond: (millisecond % 1000) * 1000000}]);
});

app.get("/api/disk/fdisk", (req, res) => {
    const result = execute(`echo ${password} | sudo -S fdisk -l`);

    const current = new Date();
    const millisecond = current.getTime();

    res.json([{value: result.toString(), clock: parseInt(millisecond/1000), nanosecond: (millisecond % 1000) * 1000}]);
});

app.get("/api/disk/stat", (req, res) => {
    const result = execute(`echo ${password} | sudo -S iostat`);

    const current = new Date();
    const millisecond = current.getTime();

    res.json([{value: result.toString(), clock: parseInt(millisecond/1000), nanosecond: (millisecond % 1000) * 1000}]);
});

app.listen(port, () => console.log('application running'));
