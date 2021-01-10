import React from 'react';

export default class NavigationBarCollapseItem extends React.Component {
    render() {
        return (<a className="collapse-item" href={this.props.href}>{this.props.name}</a>);
    }
}