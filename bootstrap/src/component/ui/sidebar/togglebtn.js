import React from 'react';
import Sidebar from '.';

export default class SidebarToggleBtn extends React.Component {
    render() {
        return (
            <div className="text-center d-none d-md-inline">
                <button className="rounded-circle border-0 sidebar-toggle-btn" onClick={Sidebar.toggle}></button>
            </div>
        );
    }
}