import React from 'react';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';

export default class SidebarBrand extends React.Component {
    render() {
        return (
            <a className="sidebar-brand d-flex align-items-center justify-content-center" href={this.props.href}>
                <div className="sidebar-brand-icon">
                    <FontAwesomeIcon icon={["fas", "laugh-wink"]} />
                </div>
                <div class="sidebar-brand-text mx-3">
                    datamon <sup>0.0.1</sup>
                </div>
            </a>
        );
    }
}