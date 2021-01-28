/**
 * 
 */
import React, { Component } from 'react';

import bootstrap from 'bootstrap/dist/js/bootstrap.bundle';

import Strings from '../../util/strings';

import Contextual from '../contextual';
import Breakpoint from '../breakpoint';

export default class Popover extends Component {
    static get lg(){ return Breakpoint.lg; }
    static get sm(){ return Breakpoint.sm; }

    static size(type){
        switch(type){
            case Popover.sm: return Breakpoint.name('btn', type);
            case Popover.lg: return Breakpoint.name('btn', type);
        }
        return undefined;
    }
    constructor(props) {
        super(props);

        this.node = null;
        this.popover = null;

        this.onShow = this.onShow.bind(this);
        this.onShown = this.onShown.bind(this);
        this.onHide = this.onHide.bind(this);
        this.onHidden = this.onHidden.bind(this);
        this.onInserted = this.onInserted.bind(this);
    }

    componentDidMount(){
        this.popover = new bootstrap.Popover(this.node);

        this.node.addEventListener('show.bs.popover', this.onShow);
        this.node.addEventListener('shown.bs.popover', this.onShown);
        this.node.addEventListener('hide.bs.popover', this.onHide);
        this.node.addEventListener('hidden.bs.popover', this.onHidden);
        this.node.addEventListener('inserted.bs.popover', this.onInserted);
    }
    componentWillUnmount() {
        this.popover = null;

        this.node.removeEventListener('show.bs.popover', this.onShow);
        this.node.removeEventListener('shown.bs.popover', this.onShown);
        this.node.removeEventListener('hide.bs.popover', this.onHide);
        this.node.removeEventListener('hidden.bs.popover', this.onHidden);
        this.node.removeEventListener('inserted.bs.popover', this.onInserted);
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

    show() {

    }

    toogle() {

    }

    hide() {

    }
    
    enable() {

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
            size,
            title,
            content,
            container,
            placement,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            'btn',
            Contextual.name('btn', contextual),
            Popover.size(size)
        ]);

        const props = Object.assign(additional,
            container ? { 'data-bs-container': container } : undefined,
            placement ? { 'data-bs-placement': placement } : undefined,
        );

        return (
            <button ref={node=>this.node = node}
                    type="button"
                    className={classNames}
                    data-bs-toggle="popover"
                    title={title}
                    data-bs-content={content} {...props}>{children}</button>
        );
    }
}