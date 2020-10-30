import React from 'react';
import SidebarBrand from './brand';
import SidebarDivider from './divider';
import SidebarItem from './item';
import SidebarHeader from './header';
import SidebarCollapse from './collapse';
import SidebarToggleBtn from './togglebtn';
import Reacts from '../../../util/reacts';
import Strings from '../../../util/strings';

/**
 * Singleton
 */
export default class Sidebar extends React.Component {
    static toggle() {
        console.log("toggle");
        if(Sidebar.__singleton) {
            Sidebar.__singleton._toggle();
        } else {
            throw new Error();
        }
    }

    static __singleton = null;

    constructor(props) {
        super(props);

        this.state = {
            toggle: false
        };

        if(Sidebar.__singleton) {
            throw new Error();
        }

        Sidebar.__singleton = this;

        this._toggle = this._toggle.bind(this);
    }
    
    _toggle() {
        this.setState({toggle: !this.state.toggle});
    }

    render() {
        console.log(this.state.toggle);
        const className = Strings.join(["navbar-nav", "bg-primary", "gradient", "sidebar", "sidebar-dark", "accordion", this.state.toggle ? "toggle" : null]);
        console.log(className);
        return (
            <ul className={className}>
                <SidebarBrand icon={["fas", "laugh-wink"]} name="Datamon" version="0.0.1" />
                <SidebarDivider className="my-0" />
                <SidebarItem icon={["fas", "tachometer-alt"]} name="Dashboard" />
                <SidebarDivider />
                <SidebarHeader name="interface" />
                <SidebarCollapse icon={["fas", "cog"]} name="Component">
                    <SidebarCollapse.Title name="Custom Component" href="#" />
                    <SidebarCollapse.Item name="Button" href="#" />
                    <SidebarCollapse.Item name="Card" href="#" />
                </SidebarCollapse>
                <SidebarCollapse icon={["fas", "wrench"]} name="Utilities">
                    <SidebarCollapse.Title name="Custom Utilities" href="#" />
                    <SidebarCollapse.Item name="Colors" href="#" />
                    <SidebarCollapse.Item name="Borders" href="#" />
                    <SidebarCollapse.Item name="Animations" href="#" />
                    <SidebarCollapse.Item name="Other" href="#" />
                </SidebarCollapse>
                <SidebarDivider />
                <SidebarHeader name="addons" />
                <SidebarCollapse icon={["fas", "folder"]} name="Page">
                    <SidebarCollapse.Title name="Login Screens" href="#" />
                    <SidebarCollapse.Item name="Login" href="#" />
                    <SidebarCollapse.Item name="Register" href="#" />
                    <SidebarCollapse.Item name="Forgot Password" href="#" />
                    <SidebarCollapse.Title name="Other Pages" href="#" />
                    <SidebarCollapse.Item name="404 Page" href="#" />
                    <SidebarCollapse.Item name="Blank Page" href="#" />
                </SidebarCollapse>
                <SidebarItem icon={["fas", "chart-area"]} name="Charts" />
                <SidebarItem icon={["fas", "table"]} name="Tables" />
                <SidebarDivider />
                <SidebarToggleBtn />
            </ul>
        );
    }
}

Sidebar.Brand = SidebarBrand;
Sidebar.Divvider = SidebarDivider;
Sidebar.Item = SidebarItem;
Sidebar.Header = SidebarHeader;
Sidebar.Collapse = SidebarCollapse;
Sidebar.ToggleBtn = SidebarToggleBtn;
