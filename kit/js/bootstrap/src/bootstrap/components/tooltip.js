/**
 * 
 */
import React, { Component } from 'react';
import Bootstrap from 'bootstrap/dist/js/bootstrap.bundle';

import Strings from '../../util/strings';

import Contextual from '../contextual';
import Breakpoint from '../breakpoint';

export default class Tooltip extends Component {
    constructor(props) {
        super(props);

        this.node = null;
        this.tooltip = null;

        this.onShow = this.onShow.bind(this);
        this.onShown = this.onShown.bind(this);
        this.onHide = this.onHide.bind(this);
        this.onHidden = this.onHidden.bind(this);
        this.onInserted = this.onInserted.bind(this);
    }

    componentDidMount() {
        this.tooltip = new Bootstrap.Tooltip(this.node);

        this.node.addEventListener('show.bs.tooltip', this.onShow);
        this.node.addEventListener('shown.bs.tooltip', this.onShown);
        this.node.addEventListener('hide.bs.tooltip', this.onHide);
        this.node.addEventListener('hidden.bs.tooltip', this.onHidden);
        this.node.addEventListener('inserted.bs.tooltip', this.onInserted);
    }

    componentWillUnmount() {
        this.tooltip = null;

        this.node.removeEventListener('show.bs.tooltip', this.onShow);
        this.node.removeEventListener('shown.bs.tooltip', this.onShown);
        this.node.removeEventListener('hide.bs.tooltip', this.onHide);
        this.node.removeEventListener('hidden.bs.tooltip', this.onHidden);
        this.node.removeEventListener('inserted.bs.tooltip', this.onInserted);
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
        if(this.props.onHidden) {
            this.props.onHidden(event);
        }
    }

    onInserted(event) {
        if(this.props.onHidden) {
            this.props.onInserted(event);
        }
    }

    show(){

    }

    hide() {

    }

    toggle() {

    }

    enable() {

    }

    disable() {

    }
    
    toggleEnabled() {

    }

    update() {

    }

    render() {
        const {
            onShow,
            onShown,
            onHide,
            onHidden,
            onInserted,
            className,
            children,
            contextual,
            placement,
            html,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            "btn",
            Contextual.name('btn', contextual)
        ]);

        const props = Object.assign(additional,
            {},
            html ? { 'data-bs-html': true } : undefined
        );

        return (
            <button ref={node => this.node = node}
                    type="button"
                    className={classNames}
                    data-bs-toggle="tooltip"
                    data-bs-placement={placement}
                    {...props}>{children}</button>
        );
    }
}