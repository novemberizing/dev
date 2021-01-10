import React from 'react';

export default class SidebarCollapseTitle extends React.Component {
    render() {
        return (<h6 className="collapse-header">{this.props.name}:</h6>);
    }
}