import React from 'react';

export default class NavigationBarHead extends React.Component {
    render() {
        return (
            <div className="sidebar-heading">
                {this.props.name}
            </div>
        );
    }
}