import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import SidebarCollapseTitle from './title';
import SidebarCollapseItem from './item';
import Reacts from "../../../../util/reacts";

export default class SidebarCollapse extends React.Component {
    static hideall() {
        SidebarCollapse.__collapses.forEach(o => o.hide());
    }
    
    static __collapses = [];
    constructor(props) {
        super(props);

        this.state = {
            visible: false
        };

        this.toggle = this.toggle.bind(this);
        this.hide = this.hide.bind(this);

        SidebarCollapse.__collapses.push(this);
    }

    hide(){
        this.setState({visible: false});
    }

    toggle() {
        if(!this.state.visible) {
            SidebarCollapse.__collapses.forEach(o => o.hide());
        }
        this.setState({visible: !this.state.visible});
    }

    render() {
        return (
            <li className="nav-item">
                <a className="nav-link collapsed" href="#" data-toggle="collapse" onClick={this.toggle}>
                    <FontAwesomeIcon icon={this.props.icon} fixedWidth />
                    <span className="sidebar-link-title">{this.props.name}</span>
                </a>
                {Reacts.display(this.state.visible, (
                    <div className="collapse" style={{display: "block"}}>
                        <div className="bg-white py-2 collapse-inner rounded">
                            {this.props.children}
                        </div>
                    </div>
                ))}
            </li>
        );
    }
}

SidebarCollapse.Title = SidebarCollapseTitle;
SidebarCollapse.Item = SidebarCollapseItem;