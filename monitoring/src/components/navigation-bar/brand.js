import React from 'react';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';

export default class NavigationBarBrand extends React.Component {
    render() {
        return (
            <a className="sidebar-brand d-flex align-items-center justify-content-center" href={this.props.href}>
                <div className="sidebar-brand-icon rotate-n-15">
                    <FontAwesomeIcon icon={["fas", "laugh-wink"]} />
                </div>
                <div className="sidebar-brand-text mx-3">{this.props.title} <sup>{this.props.version}</sup></div>
            </a>
        );
    }
}