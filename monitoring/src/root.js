import React from 'react';
import NavigationBar from './components/navigation-bar';
import Page from './components/page';
import Content from './components/content';
import Toolbar from './components/toolbar';
import ToolbarNav from './components/toolbar/navigation';

export default class Root extends React.Component {
    render() {
        return (<div id="wrapper">
            <NavigationBar>
                <NavigationBar.Brand title="datamon" href="/" version="0.0.1" />
                <NavigationBar.Divider className={['my-0']} />
                <NavigationBar.Link icon={["fas", "tachometer-alt"]} name="Dashboard" />
                <NavigationBar.Divider />
                <NavigationBar.Head name="Interface" />
                <NavigationBar.Collapse icon={["fas", "cog"]} name="Components">
                    <NavigationBar.Collapse.Header name="Custom Component" />
                    <NavigationBar.Collapse.Item href="#" name="Button" />
                    <NavigationBar.Collapse.Item href="#" name="Card" />
                </NavigationBar.Collapse>
                <NavigationBar.Collapse icon={["fas", "wrench"]} name="Utiliities">
                    <NavigationBar.Collapse.Header name="Custom Utilities" />
                    <NavigationBar.Collapse.Item href="#" name="Colors" />
                    <NavigationBar.Collapse.Item href="#" name="Borders" />
                    <NavigationBar.Collapse.Item href="#" name="Animations" />
                    <NavigationBar.Collapse.Item href="#" name="Other" />
                </NavigationBar.Collapse>
                <NavigationBar.Divider />
                <NavigationBar.Head name="ADDONS" />
                <NavigationBar.Collapse icon={["fas", "folder"]} name="Pages">
                    <NavigationBar.Collapse.Header name="Login Screens" />
                    <NavigationBar.Collapse.Item href="#" name="Login" />
                    <NavigationBar.Collapse.Item href="#" name="Register" />
                    <NavigationBar.Collapse.Item href="#" name="Forgot Password" />
                    <NavigationBar.Divider />
                    <NavigationBar.Collapse.Header name="Other Pages" />
                    <NavigationBar.Collapse.Item href="#" name="404 Page" />
                    <NavigationBar.Collapse.Item href="#" name="Blank Page" />
                </NavigationBar.Collapse>
                <NavigationBar.Link icon={["fas", "chart-area"]} name="Charts" />
                <NavigationBar.Link icon={["fas", "table"]} name="Tables" />
                <NavigationBar.Divider className={["d-none","d-md-block"]} />
                <NavigationBar.Toggle />
            </NavigationBar>
            <Content>
                <Toolbar>
                    <Toolbar.Btn className="d-md-none" icon={["fa", "bars"]} />
                    <Toolbar.Search />
                    <Toolbar.Nav>
                        <ToolbarNav.Dropdown.Search />
                        <ToolbarNav.Dropdown.Alarm />
                        <ToolbarNav.Dropdown.Message />
                    </Toolbar.Nav>
                </Toolbar>
                <Page>
                    Hello
                </Page>
            </Content>
        </div>);
    }
}
