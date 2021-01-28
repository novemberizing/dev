import React, { Component } from 'react';

import Range from '../../components/input/range';

import Context from '../../context';

export default class ExampleFormRangeView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** STEP */}
                    <div style={{padding: '5px'}}>
                        <Range id="customRange4" min={0} max={5} step={0.25}>Example Range</Range>
                    </div>
                    {/** MIN: MAX */}
                    <div style={{padding: '5px'}}>
                        <Range id="customRange3" min={0} max={5}>Example Range</Range>
                    </div>
                    {/** RANGE: DISABLED */}
                    <div style={{padding: '5px'}}>
                        <Range id="customRange2" disabled>Example Range</Range>
                    </div>
                    {/** RANGE */}
                    <div style={{padding: '5px'}}>
                        <Range id="customRange1">Example Range</Range>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}