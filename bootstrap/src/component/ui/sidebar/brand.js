import React from 'react';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';

export default class SidebarBrand extends React.Component {
    render() {
        return (
            <a className="sidebar-brand d-flex align-items-center justify-content-center" href={this.props.href}>
                <div className="sidebar-brand-icon">
                    <FontAwesomeIcon icon={this.props.icon} />
                </div>
                <div className="sidebar-brand-text mx-3">
                    {this.props.name}
                    {this.props.version && <sup>{this.props.version}</sup>}
                </div>
            </a>
        );
    }
}