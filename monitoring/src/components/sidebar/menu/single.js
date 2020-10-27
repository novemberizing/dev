import React from 'react';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';

export default class SidebarSingleMenuItem extends React.Component {
    render() {
        return (
            <li className="nav-item active">
                <a href="/index.html" className="nav-link">
                    <FontAwesomeIcon icon={this.props.icon} fixedWidth />
                    <span>{this.props.name}</span>
                </a>
            </li>
        );
    }
}