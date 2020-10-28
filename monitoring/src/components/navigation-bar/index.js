import React from "react";
import NavigationBarBrand from "./brand";
import NavigationBarCollapse from "./collapse";
import NavigationBarDivider from "./divider";
import NavigationBarHead from "./head";
import NavigationBarItem from "./item";
import NavigationBarLink from "./link";
import NavigationBarToggle from "./toggle";

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
NavigationBar.Divider = NavigationBarDivider;
NavigationBar.Item = NavigationBarItem;
NavigationBar.Link = NavigationBarLink;
NavigationBar.Head = NavigationBarHead;
NavigationBar.Collapse = NavigationBarCollapse;
NavigationBar.Toggle = NavigationBarToggle;