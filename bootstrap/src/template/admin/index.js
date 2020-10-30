import React from 'react';

import Sidebar from '../../component/ui/sidebar';
import Toolbar from '../../component/ui/topbar';

export default class TemplateAdmin extends React.Component {
    render() {
        return (
            <div className="all">
                <Sidebar>
                    <Sidebar.Brand icon={["fas", "laugh-wink"]} name="Datamon" version="0.0.1" />
                    <Sidebar.Divider className="my-0" />
                    <Sidebar.Item icon={["fas", "tachometer-alt"]} name="Dashboard" />
                    <Sidebar.Divider />
                    <Sidebar.Header name="interface" />
                    <Sidebar.Collapse icon={["fas", "cog"]} name="Component">
                        <Sidebar.Collapse.Title name="Custom Component" href="#" />
                        <Sidebar.Collapse.Item name="Button" href="#" />
                        <Sidebar.Collapse.Item name="Card" href="#" />
                    </Sidebar.Collapse>
                    <Sidebar.Collapse icon={["fas", "wrench"]} name="Utilities">
                        <Sidebar.Collapse.Title name="Custom Utilities" href="#" />
                        <Sidebar.Collapse.Item name="Colors" href="#" />
                        <Sidebar.Collapse.Item name="Borders" href="#" />
                        <Sidebar.Collapse.Item name="Animations" href="#" />
                        <Sidebar.Collapse.Item name="Other" href="#" />
                    </Sidebar.Collapse>
                    <Sidebar.Divider />
                    <Sidebar.Header name="addons" />
                    <Sidebar.Collapse icon={["fas", "folder"]} name="Page">
                        <Sidebar.Collapse.Title name="Login Screens" href="#" />
                        <Sidebar.Collapse.Item name="Login" href="#" />
                        <Sidebar.Collapse.Item name="Register" href="#" />
                        <Sidebar.Collapse.Item name="Forgot Password" href="#" />
                        <Sidebar.Collapse.Title name="Other Pages" href="#" />
                        <Sidebar.Collapse.Item name="404 Page" href="#" />
                        <Sidebar.Collapse.Item name="Blank Page" href="#" />
                    </Sidebar.Collapse>
                    <Sidebar.Item icon={["fas", "chart-area"]} name="Charts" />
                    <Sidebar.Item icon={["fas", "table"]} name="Tables" />
                    <Sidebar.Divider />
                    <Sidebar.ToggleBtn />
                </Sidebar>
                <div className="page d-flex flex-column">
                    <Toolbar>

                    </Toolbar>
                    <div className="container-fluid">
                        Hello World
                    </div>
                </div>
            </div>
        );
    }
}