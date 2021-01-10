import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Strings from '../../../../util/string';
import ToolbarNavDropdownAlarm from './alarm';
import ToolbarNavDropdownSearch from './search';
import ToolbarNavDropdownMessage from "./message";
import ToolbarNavDropdownProfile from "./profile";

export default class ToolbarNavDropdown extends React.Component {
    static __dropdowns = [];

    constructor(props){
        super(props);
        this.state = {
            visible: false
        }

        this.toggle = this.toggle.bind(this);

        ToolbarNavDropdown.__dropdowns.push(this);
    }

    hide() {
        this.setState({visible: false});
    }

    toggle() {
        if(this.state.visible) {
            this.setState({visible: false});
        } else {
            ToolbarNavDropdown.__dropdowns.forEach(o => o.hide());
            this.setState({visible: true});
        }
    }

    render() {
        const styles = ["nav-item", "dropdown", "no-arrow"];
        return (
            <li className={Strings.concat([styles, this.props.className])}>
                <a className="nav-link dropdown-toggle" href="#" onClick={this.toggle}>
                    { this.props.icon && <FontAwesomeIcon icon={this.props.icon} fixedWidth />}
                    { this.props.count > 0 && <span className="badge badge-danger badge-counter">{this.props.count}</span>}
                </a>
                {this.state.visible && this.props.children}
            </li>
        );
    }
}

ToolbarNavDropdown.Search = ToolbarNavDropdownSearch;
ToolbarNavDropdown.Alarm = ToolbarNavDropdownAlarm;
ToolbarNavDropdown.Message = ToolbarNavDropdownMessage;
ToolbarNavDropdown.Profile = ToolbarNavDropdownProfile;
