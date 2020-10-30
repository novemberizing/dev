import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import SidebarCollapse from './collapse';

export default class SidebarItem extends React.Component {
    render() {
        return (
            <li className="nav-item">
                <a className="nav-link" href="#" onClick={SidebarCollapse.hideall}>
                    <FontAwesomeIcon icon={this.props.icon} fixedWidth />
                    <span className="sidebar-link-title">{this.props.name}</span>
                </a>
            </li>
        );
    }
}