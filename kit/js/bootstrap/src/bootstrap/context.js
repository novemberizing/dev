/**
 * BASIC ABSTRACT ELEMENT (Context)
 * 
 */

import React, { Component } from 'react';
import Collections from '../util/collections';

export default class Context extends Component {
    static context = React.createContext({type: []});
    static Provider = Context.context.Provider;
    static contextType = Context.context;

    static push(types, type) {
        if(Collections.last(types) !== type) {
            return Collections.push(types, type);
        }
        return types;
    }

    constructor(props) {
        super(props);
    }
}