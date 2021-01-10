import React from 'react';
import SidebarDivider from './divider';

export default class SidebarHeader extends React.Component {
    render() {
        return (<div className="sidebar-heading">{this.props.name}</div>);
    }
}