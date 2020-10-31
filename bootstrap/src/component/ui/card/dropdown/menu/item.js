import React from 'react';

export default class DropdownCardMenuItem extends React.Component {
    render() {
        return (<a className="dropdown-item" href={this.props.href}>{this.props.name}</a>);
    }
}