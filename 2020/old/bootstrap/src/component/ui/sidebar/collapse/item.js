import { library } from '@fortawesome/fontawesome-svg-core'
import React from 'react';

export default class SidebarCollapseItem extends React.Component {
    render() {
        return (<a href={this.props.href} className="collapse-item">{this.props.name}</a>);
    }
}