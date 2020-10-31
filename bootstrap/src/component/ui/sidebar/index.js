import React from 'react';

import SidebarBrand from './brand';
import SidebarDivider from './divider';
import SidebarItem from './item';
import SidebarHeader from './header';
import SidebarCollapse from './collapse';
import SidebarToggleBtn from './togglebtn';

import Strings from '../../../util/strings';

/**
 * Singleton
 */
export default class Sidebar extends React.Component {
    static __listeners = [];

    static status() {
        return Sidebar.__singleton.state.toggle;
    }

    static on(f) {
        Sidebar.__listeners.push(f);
    }

    static off(f) {
        Sidebar.__listeners = Sidebar.__listeners.filter(o => (o !== f));
    }

    static toggle() {
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

    componentDidUpdate() {
        Sidebar.__listeners.forEach(f => {
            f(this.state);
        });
    }

    componentWillUnmount() {
        Sidebar.__listeners = [];
    }

    render() {
        const className = Strings.join(["navbar-nav", "bg-primary", "gradient", "sidebar", "sidebar-dark", "accordion", this.state.toggle ? "toggle" : null]);
        return (
            <ul className={className}>
                {this.props.children}
            </ul>
        );
    }
}

Sidebar.Brand = SidebarBrand;
Sidebar.Divider = SidebarDivider;
Sidebar.Header = SidebarHeader;
Sidebar.Item = SidebarItem;
Sidebar.Collapse = SidebarCollapse;
Sidebar.ToggleBtn = SidebarToggleBtn;
