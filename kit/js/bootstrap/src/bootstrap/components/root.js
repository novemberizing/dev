import React from 'react';

import Context from '../context';

export default class Root extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type: []}}>
                {this.props.children}
            </Context.Provider>
        );
    }
}