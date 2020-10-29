import React from 'react';
import Strings from '../../util/strings';

export default class BreadcrumbItem extends React.Component {
    render() {
        return (<li data-content={this.props.separator || "/"} className={Strings.join(["breadcrumb-item", this.props.active ? "active" : null])} aria-current="page">{this.props.children}</li>);
    }
}