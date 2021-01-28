/**
 * 
 */
import React from 'react';
import Collections from '../../util/collections';
import Strings from '../../util/strings';

import Context from '../context';
import Contextual from '../contextual';
import ListItem from './list/item';

export default class Dropdown extends Context {
    static get sm(){ return 'sm'; }
    static get lg(){ return 'lg'; }

    static size(prefix, type, suffix, separator = '-') {
        switch(type) {
            case Dropdown.sm: return Strings.join([prefix, type, suffix], separator);
            case Dropdown.lg: return Strings.join([prefix, type, suffix], separator);
        }
        return undefined;
    }

    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            name,
            id,
            expanded,
            contextual,
            split,
            size,
            dark,
            type,
            outline,
            ...additional
        } = this.props;

        const parent = Collections.last(this.context.type);
        
        const classNames = Strings.join([
            className,
            "dropdown",
            (parent === "btn-group" || split) && 'btn-group'
        ]);

        const props = Object.assign(additional,
            {}
        );
        
        const listitem = Collections.find(parent, ["nav", "tab"]);
        const nav = Collections.find(parent, ["nav", "tab"]);

        const context = {
            type: Context.push(this.context.type, "dropdown")
        };

        const elements = type === 'link' ?
            [
                split &&  <a key={0} className={Strings.join([Dropdown.size('btn', size), Contextual.name(outline ? 'btn-outline' : 'btn', contextual)])} type="button">{name}</a>,
                split &&  <a key={1} className={Strings.join([Dropdown.size('btn', size), Contextual.name(outline ? 'btn-outline' : 'btn', contextual), nav && 'nav-link','dropdown-toggle', 'dropdown-toggle-split'])} type="button" id={id} data-bs-toggle="dropdown" aria-expanded={expanded===true}></a>,
                !split && <a key={2} className={Strings.join([Dropdown.size('btn', size), Contextual.name(outline ? 'btn-outline' : 'btn', contextual), nav && 'nav-link', 'dropdown-toggle'])} type="button" id={id} data-bs-toggle="dropdown" aria-expanded={expanded===true}>{name}</a>,
                <ul key={3} className={Strings.join(["dropdown-menu", dark && 'dropdown-menu-dark'])} aria-labelledby={id}>
                    {children}
                </ul>
            ]
          : [
                split &&  <button key={0} className={Strings.join(["btn", Dropdown.size('btn', size), Contextual.name(outline ? 'btn-outline' : 'btn', contextual)])} type="button">{name}</button>,
                split &&  <button key={1} className={Strings.join(["btn", Dropdown.size('btn', size), Contextual.name(outline ? 'btn-outline' : 'btn', contextual), nav && 'nav-link','dropdown-toggle', 'dropdown-toggle-split'])} type="button" id={id} data-bs-toggle="dropdown" aria-expanded={expanded===true}></button>,
                !split && <button key={2} className={Strings.join(["btn", Dropdown.size('btn', size), Contextual.name(outline ? 'btn-outline' : 'btn', contextual), nav && 'nav-link', 'dropdown-toggle'])} type="button" id={id} data-bs-toggle="dropdown" aria-expanded={expanded===true}>{name}</button>,
                <ul key={3} className={Strings.join(["dropdown-menu", dark && 'dropdown-menu-dark'])} aria-labelledby={id}>
                    {children}
                </ul>
            ];

        return (
            <Context.Provider value={context}>
                {listitem ? <ListItem className={classNames} {...props}>{elements}</ListItem>
                          : parent === 'input-group' ? elements
                                                     : <div className={classNames} {...props}>{elements}</div>}
            </Context.Provider>
        );
    }
}