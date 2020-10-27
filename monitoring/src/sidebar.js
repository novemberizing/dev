import React from 'react';
import SidebarDivider from './components/sidebar/divider';
import SidebarBrand from './components/sidebar/brand';
import SidebarSingleMenuItem from './components/sidebar/menu/single';
import SidebarHeadline from './components/sidebar/headline';
import SidebarCollapseMenu from './components/sidebar/menu/collapse';

export default class Sidebar extends React.Component {
    render() {
        return (
            <ul className="navbar-nav bg-gradient-primary sidebar sidebar-dark accordion">
                <SidebarBrand name="DATAMON" icon={['fas', 'tachometer-alt']} />
                <SidebarDivider />
                <SidebarSingleMenuItem name="DASHBOARD" icon={['fas', 'tachometer-alt']} />
                <SidebarDivider />
                <SidebarHeadline name="INTERFACE" />
                <SidebarCollapseMenu name="COMPONENT" icon={['fas', 'cog']}>
                    <SidebarCollapseMenu.Item />
                    <SidebarCollapseMenu.Item />
                    <SidebarCollapseMenu.Item />
                </SidebarCollapseMenu>
            </ul>
        );
    }
}