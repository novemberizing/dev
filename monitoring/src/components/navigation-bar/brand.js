import React from 'react';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';

export default class NavigationBarBrand extends React.Component {
    render() {
        return (
            <a href={this.props.href} className="sidebar-brand d-flex align-items-center justify-content-center">
                <div className="sidebar-brand-icon">
                    <FontAwesomeIcon icon={this.props.icon} />
                </div>
                <div className="sidebar-brand-text mx-3">NOV ADMIN <sup>1</sup></div>
            </a>
        );
    }
}