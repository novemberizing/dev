import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import NavigationBarCollapseHeader from './header';
import NavigationBarCollapseItem from './item';


/**
 * 
 * @todo    implement collapse menu transition
 */
export default class NavigationBarCollapse extends React.Component {
    static __collapses = [];

    constructor(props) {
        super(props);
        this.state = {
            visible: false
        }

        this.toggle = this.toggle.bind(this);
        this.hide = this.hide.bind(this);

        NavigationBarCollapse.__collapses.push(this);
    }

    hide() {
        this.setState({visible: false});
    }

    toggle() {
        if(this.state.visible) {
            this.setState({visible: false});
        } else {
            NavigationBarCollapse.__collapses.forEach(o=>o.hide());
            this.setState({visible: true});
        }
    }

    render() {
        return (
            <li className="nav-item">
                <a className="nav-link collapsed" href="#" onClick={this.toggle}>
                    { this.props.icon && <FontAwesomeIcon icon={this.props.icon} fixedWidth />}
                    <span className="sidebar-link-title">{this.props.name}</span>
                </a>
                { this.state.visible && <div className="collapse" style={{display:'block'}}>
                    <div className="bg-white py-2 collapse-inner rounded">
                        {this.props.children}
                    </div>
                </div>}
            </li>
        );
    }    
}

NavigationBarCollapse.Item = NavigationBarCollapseItem;
NavigationBarCollapse.Header = NavigationBarCollapseHeader;