import express from "express";
import cors from "cors";
import { exec, execSync as execute } from "child_process";

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
    // res.send("Hello World!");
});

app.listen(port, () => console.log('application running'));
