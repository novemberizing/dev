import React from 'react';
import NavigationBarBrand from './navigation-bar/brand';

export default class NavigationBar extends React.Component {

    render() {
        return (
            <ul className="navbar-nav bg-gradient-primary sidebar sidebar-dark accordion">
                {this.props.children}
            </ul>
        );
    }
}

NavigationBar.Brand = NavigationBarBrand;
