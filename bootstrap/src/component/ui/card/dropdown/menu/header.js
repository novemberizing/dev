import React from 'react';

export default class DropdownCardMenuHeader extends React.Component {
    render() {
        return (<div className="dropdown-header">{this.props.name}:</div>);
    }
}