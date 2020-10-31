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
    static onChangeListener = [];

    static status() {
        return Sidebar.__singleton.state.toggle;
    }

    static onChange(f) {
        Sidebar.onChangeListener.push(f);
    }

    static removeOnChange(f) {
        Sidebar.onChangeListener = Sidebar.onChangeListener.filter(o => (o !== f));
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
        Sidebar.onChangeListener.forEach(f => {
            f(this.state);
        });
    }

    componentWillUnmount() {
        Sidebar.onChangeListener = [];
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
