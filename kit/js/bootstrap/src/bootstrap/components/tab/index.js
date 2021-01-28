/**
 * 
 */
import React from 'react';

import Strings from '../../../util/strings';
import Collections from '../../../util/collections';

import Context from '../../context';
import Hyperlink from '../hyperlink';
import Dropdown from '../dropdown';
import Panel from '../panel';

export default class Tab extends Context {
    constructor(props) {
        super(props);
        this.node = null;

        this.onShow = this.onShow.bind(this);
        this.onShown = this.onShown.bind(this);
        this.onHide = this.onHide.bind(this);
        this.onHidden = this.onHidden.bind(this);
    }

    show() {
        
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

    componentDidMount() {
        this.node.addEventListener('show.bs.tab', this.onShow);
        this.node.addEventListener('shown.bs.tab', this.onShown);
        this.node.addEventListener('hide.bs.tab', this.onHide);
        this.node.addEventListener('hidden.bs.tab', this.onHidden);
    }

    componentWillUnmount() {
        this.node.removeEventListener('show.bs.tab', this.onShow);
        this.node.removeEventListener('shown.bs.tab', this.onShown);
        this.node.removeEventListener('hide.bs.tab', this.onHide);
        this.node.removeEventListener('hidden.bs.tab', this.onHidden);
    }

    panelLink(item, index) {
        return <li key={index} className="nav-item" role="presentation">
                   <a href={`#${item.props.id}`}
                      className={Strings.join(["nav-link", item.props.active && 'active'])}
                      id={`#${item.props.id}-tab`}
                      data-bs-toggle="tab"
                      aria-controls={`#${item.props.id}`}
                      aria-selected={item.props.active===true}>{item.props.name}</a></li>;
    }

    render() {
        const {
            className,
            children,
            role,
            pill,
            vertical,
            onShow,
            onShown,
            onHide,
            onHidden,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            vertical && "flex-column",
            pill ? "nav nav-pills" : "nav nav-tabs",
            Collections.last(this.context.type) === 'card' && (pill ? "card-header-pills" : "card-header-tabs")
        ]);

        const props = Object.assign(additional,
            vertical ? { 'aria-orientation': "vertical" } : undefined
        );

        const context = {
            type: Context.push(this.context.type, "tab")
        };

        const panels = Collections.filter(children, item => item.type === Panel);
        const hyperlinks = Collections.map(panels, (item, index) => this.panelLink(item, index));
        const elements = Collections.filter(children, item => item.type === Hyperlink || item.type === Dropdown)
                                    .concat(hyperlinks);

        return (
            <Context.Provider value={context}>
                <ul ref={node => this.node = node} className={classNames} {...props} role={role}>{elements}</ul>
                {Collections.exist(panels) && <div className="tab-content">{panels}</div>}
            </Context.Provider>
        );
    }
}