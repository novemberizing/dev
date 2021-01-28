/**
 * 
 */
import React from 'react';

import Context from '../context';

import Strings from '../../util/strings';
import Collections from '../../util/collections';

export default class Collapse extends Context {
    constructor(props) {
        super(props);

        this.node = null;

        this.onShow = this.onShow.bind(this);
        this.onShown = this.onShown.bind(this);
        this.onHide = this.onHide.bind(this);
        this.onHidden = this.onHidden.bind(this);
    }

    onShow(event) {
        if(this.props.onShow) {
            this.props.onShow(event);
        }
    }

    onShown(event) {
        if(this.props.onShown) {
            this.props.onShown(event);
        }
    }

    onHide(event) {
        if(this.props.onHide) {
            this.props.onHide(event);
        }
    }

    onHidden(event) {
        if(this.props.onHide) {
            this.props.onHidden(event);
        }
    }

    componentDidMount() {
        this.node.addEventListener('show.bs.collapse', this.onShow);
        this.node.addEventListener('shown.bs.collapse', this.onShown);
        this.node.addEventListener('hide.bs.collapse', this.onHide);
        this.node.addEventListener('hidden.bs.collapse', this.onHidden);
    }

    componentWillUnmount() {
        this.node.removeEventListener('show.bs.collapse', this.onShow);
        this.node.removeEventListener('shown.bs.collapse', this.onShown);
        this.node.removeEventListener('hide.bs.collapse', this.onHide);
        this.node.removeEventListener('hidden.bs.collapse', this.onHidden);
    }

    render() {
        const {
            className,
            id,
            multi,
            onShow,
            onShown,
            onHide,
            onHidden,
            children,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            "collapse",
            multi && 'multi-collapse',
            Collections.last(this.context.type, "navbar") && "navbar-collapse"
        ]);

        const props = Object.assign(additional,
            {}
        );

        return (<div ref={node=>this.node=node} className={classNames} id={id} {...props}>{children}</div>);
    }
}