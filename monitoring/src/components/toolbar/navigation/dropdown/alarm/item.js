import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import React from "react";
import Strings from '../../../../../util/string';

export default class ToolbarNavDropdownAlarmItem extends React.Component {
    render() {
        return (
            <a className="dropdown-item d-flex align-items-center" href="#">
                <div className="mr-3">
                    <div className={Strings.concat(["icon-circle", this.props.bg])}>
                        <FontAwesomeIcon icon={this.props.icon} className="text-white" />
                    </div>
                </div>
                <div>
                    <div className="small text-gray-500">{this.props.date}</div>
                    { this.props.bold ? <span className="font-weight-bold">{this.props.content}</span> : this.props.content }
                </div>
            </a>
        );
    }
}