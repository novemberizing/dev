/**
 * TOOLTOP & POPOVER 는 정상적으로 동작하지 않아서 아직 미구현.
 */
import React from 'react';

import Strings from '../../util/strings';
import Collections from '../../util/collections';

import Context from '../context';
import Breakpoint from '../breakpoint';

export default class Modal extends Context {
    static get xl(){ return Breakpoint.xl; }
    static get sm(){ return Breakpoint.sm; }
    static get lg(){ return Breakpoint.lg; }

    static size(type) {
        switch(type) {
            case Modal.xl:  return Breakpoint.name('modal', type);
            case Modal.sm:  return Breakpoint.name('modal', type);
            case Modal.lg:  return Breakpoint.name('modal', type);
        }
        return undefined;
    }

    constructor(props) {
        super(props);

        this.node = null;

        this.onShow = this.onShow.bind(this);
        this.onShown = this.onShown.bind(this);
        this.onHide = this.onHide.bind(this);
        this.onHidden = this.onHidden.bind(this);
        this.onHidePrevented = this.onHidePrevented.bind(this);
    }

    componentDidMount() {
        this.node.addEventListener("show.bs.modal", this.onShow);
        this.node.addEventListener("shown.bs.modal", this.onShown);
        this.node.addEventListener("hide.bs.modal", this.onHide);
        this.node.addEventListener("hidden.bs.modal", this.onHidden);
        this.node.addEventListener("hidePrevented.bs.modal", this.onHidePrevented);
    }

    componentWillUnmount() {
        this.node.removeEventListener("show.bs.modal", this.onShow);
        this.node.removeEventListener("shown.bs.modal", this.onShown);
        this.node.removeEventListener("hide.bs.modal", this.onHide);
        this.node.removeEventListener("hidden.bs.modal", this.onHidden);
        this.node.removeEventListener("hidePrevented.bs.modal", this.onHidePrevented);
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

    onHidePrevented(event) {
        if(this.props.onhidePrevented) {
            this.props.onHidePrevented(event);
        }
    }

    toggle() {

    }

    show() {

    }

    hide() {

    }

    handleUpdate() {
        
    }

    render() {
        const {
            onHidePrevented,
            onShow,
            onShown,
            onHide,
            onHidden,
            className,
            children,
            fade,
            size,
            backdrop,
            keyboard,
            fullscreen,
            scrollable,
            centered,
            ...additional
        } = this.props;

        const parent = Collections.last(this.context.type);

        const classNames = Strings.join([
            className,
            "modal",
            fade && 'fade'
        ]);

        const props = Object.assign(additional, 
            backdrop ? { 'data-bs-backdrop': backdrop } : undefined,
            (keyboard || keyboard===false) ? { 'data-bs-keyboard': keyboard} : undefined,
        );

        const context = {
            type: Context.push(this.context.type, "modal")
        };

        const modalClassName = Strings.join([
            "modal-dialog",
            Modal.size(size),
            centered && "modal-dialog-centered",
            scrollable && "modal-dialog-scrollable",
            fullscreen && (Breakpoint.name('modal-fullscreen',fullscreen, 'down') || 'modal-fullscreen')
        ]);

        return (
            <Context.Provider value={context}>
                <div ref={node => this.node = node} className={classNames} tabIndex="-1" {...props}>
                    <div className={modalClassName}>
                        {children}
                    </div>
                </div>
            </Context.Provider>
        );
    }
}