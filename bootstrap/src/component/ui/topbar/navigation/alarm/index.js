import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Reacts from '../../../../../util/reacts';
import TopbarNavDropdown from '../dropdown';
import TopbarNavAlarmItem from './item';

const __example = [
    { icon: ["fas", "file-alt"], type: "primary", date: "December 12, 2019", bold: true, message: "A new monthly report is ready to download!" },
    { icon: ["fas", "donate"], type: "success", date: "December 7, 2019", bold: false, message: "$290.29 has been deposited into your account!" },
    { icon: ["fas", "exclamation-triangle"], type: "warning", date: "December 2, 2019", bold: false, message: "Spending Alert: We've noticed unusually high spending for your account." }
];

export default class TopbarNavAlarm extends TopbarNavDropdown {
    constructor(props) {
        super(props);

        this.state = {
            messages: __example
        };
    }

    messages() {
        return this.state.messages.map((o, index)=>{
            return (<TopbarNavAlarmItem icon={o.icon} type={o.type} date={o.date} bold={o.bold} message={o.message} key={index} />);
        }).concat();
    }

    render() {
        return (
            <li className="nav-item dropdown no-arrow ">
                <a className="nav-link dropdown-toggle" href="#" onClick={this.toggle}>
                    <FontAwesomeIcon icon={["fas", "bell"]} fixedWidth size="1x" />
                    <span className="badge badge-danger badge-counter">
                        {this.state.messages.length > 0 ? this.state.messages.length : ""}
                    </span>
                </a>
                {Reacts.display(this.state.visible,
                    <div className="dropdown-list dropdown-menu dropdown-menu-right shadow animated--grow-in show" aria-labelledby="alertsDropdown">
                        <h6 className="dropdown-header">
                            Alerts Center
                        </h6>
                        {this.messages()}
                        <a className="dropdown-item text-center small text-gray-500" href="#">Show All Alerts</a>
                    </div>
                )}
            </li>
        );
    }
}

TopbarNavAlarm.Item = TopbarNavAlarm;