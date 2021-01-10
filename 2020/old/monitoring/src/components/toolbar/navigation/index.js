import React from "react";
import ToolbarNavDropdown from "./dropdown";
import ToolbarNavDivider from './divider';

export default class ToolbarNav extends React.Component {
    render() {
        return (
            <ul className="navbar-nav ml-auto">
                {this.props.children}
            </ul>
        );
    }
}

ToolbarNav.Dropdown = ToolbarNavDropdown;
ToolbarNav.Divider = ToolbarNavDivider;