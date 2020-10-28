import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';

export default class NavigationBarLink extends React.Component {
    render() {
        return (
            <li className="nav-item">
                <a className="nav-link" href={this.props.href}>
                    { this.props.icon && <FontAwesomeIcon icon={this.props.icon} fixedWidth /> }
                    <span className="sidebar-link-title">{this.props.name}</span>
                </a>
            </li>
        );
    }
}