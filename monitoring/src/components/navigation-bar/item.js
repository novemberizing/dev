import React from 'react';

export default class NavigationBarItem extends React.Component {

    render() {
        return (<li className="nav-item">
            {this.props.children}
        </li>)
    }
}