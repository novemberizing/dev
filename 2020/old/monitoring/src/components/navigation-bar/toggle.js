import React from 'react';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';

export default class NavigationBarToggle extends React.Component {
    render() {
        return (
            <div className="text-center d-none d-md-inline">
                <button className="rounded-circle border-0 sidebarToggleBtn"></button>
            </div>
        );
    }
}