import React from 'react';
import Strings from '../../util/strings';

export default class Badge extends React.Component {
    static className(type, additional = []) {
        const name = Strings.join(["badge", type], "-");
        return Strings.join(["badge", name, additional])
    }

    static link(type, href, pill, className, children) {
        return (<a href={href} className={Badge.className(type, [className, pill ? "badge-pill" : null])}>{children}</a>);
    }

    static span(type, pill, className, children) {
        return (<span className={Badge.className(type, [className, pill ? "badge-pill" : null])}>{children}</span>);
    }

    render() {
        return this.props.link ? Badge.link(this.props.type, this.props.href, this.props.pill, this.props.className, this.props.children) : Badge.span(this.props.type, this.props.pill, this.props.className, this.props.children);
    }
}