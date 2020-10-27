import React from 'react';

export default class SidebarHeadline extends React.Component {
    render() {
        return (
            <div className="sidebar-heading">{this.props.name}</div>
        );
    }
}