/**
 * 
 */

import React, { Component } from 'react';

import Strings from '../../util/strings';

export default class ScrollSpy extends Component {
    constructor(props) {
        super(props);

        this.node = null;

        this.onActivate = this.onActivate.bind(this);
    }

    refresh() {

    }

    onActivate(event) {
        if(this.props.onActivate) {
            this.props.onActivate(event);
        }
    }

    componentDidMount() {
        this.node.addEventListener('activate.bs.scrollspy', this.onActivate);
    }

    componentWillUnmount() {
        this.node.removeEventListener('activate.bs.scrollspy', this.onActivate);
    }

    render() {
        const {
            onActivate,
            className,
            children,
            target,
            offset,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className
        ]);

        const props = Object.assign(additional,
            {}
        );

        return (
            <div ref={node => this.node = node}
                 data-bs-spy="scroll"
                 data-bs-target={target}
                 data-bs-offset={offset || 0}
                 tabIndex="0"
                 className={classNames}
                 {...props}>
                {children}
            </div>
        );
    }
}