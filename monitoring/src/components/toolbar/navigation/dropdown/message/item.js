import React from "react";
import Strings from "../../../../../util/string";

export default class ToolbarNavDropdownMessageItem extends React.Component {
    render() {
        return (
            <a className="dropdown-item d-flex align-items-center" href="#">
                <div className="dropdown-list-image mr-3">
                    <img className="rounded-circle" src={this.props.image} alt={this.props.alt} />
                    <div className={Strings.concat(["status-indicator", this.props.status])}></div>
                </div>
                <div className={this.props.bold ? "font-weight-bold" : ""}>
                    <div className="text-truncate">{this.props.message}</div>
                    <div className="small text-gray-500">{this.props.from} · {this.props.when}</div>
                </div>
            </a>
        );
    }
}