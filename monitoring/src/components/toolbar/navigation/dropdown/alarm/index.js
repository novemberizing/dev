import { library } from "@fortawesome/fontawesome-svg-core"
import React from "react";
import ToolbarNavDropdown from "..";
import ToolbarNavDropdownAlarmItem from "./item";

export default class ToolbarNavDropdownAlarm extends React.Component {
    constructor(props){
        super(props);

        this.state = {
            messages: [
                {
                    icon: ["fas", "file-alt"],
                    date: "December 12, 2019",
                    content: "A new monthly report is ready to download!",
                    bold: true,
                    bg: "bg-primary"
                },
                {
                    icon: ["fas", "donate"],
                    date: "December 7, 2019",
                    content: "$290.29 has been deposited into your account!",
                    bold: false,
                    bg: "bg-success"
                },
                {
                    icon: ["fas", "exclamation-triangle"],
                    date: "December 2, 2019",
                    content: "Spending Alert: We've noticed unusually high spending for your account.",
                    bold: false,
                    bg: "bg-warning"
                }
            ]
        };
    }


    render() {
        const messages = this.state.messages && (this.state.messages.map((o, index) => {
            return (<ToolbarNavDropdownAlarmItem icon={o.icon} date={o.date} content={o.content} bold={o.bold} bg={o.bg} key={index} />);
        }).concat());

        return (
            <ToolbarNavDropdown icon={["fas", "bell"]} count={this.state.messages.length}>
                <div className="dropdown-list dropdown-menu dropdown-menu-right shadow animated--grow-in" style={{display:"block"}}>
                    <h6 className="dropdown-header">
                        Alerts Center
                    </h6>
                    {messages}
                    <a className="dropdown-item text-center small text-gray-500" href="#">Show All Alerts</a>
                </div>
            </ToolbarNavDropdown>
        );
    }
}