/**
 * 
 */
import React, { Component } from 'react';

import Pagination from '../components/pagination';
import Hyperlink from '../components/hyperlink';
import Context from '../context';

export default class ExamplePaginationView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** PAGINATION: ALIGNMENT */}
                    <Pagination label="Page navigation example" className="justify-content-end">
                        <Hyperlink label="Previous" disabled>
                            <span aria-hidden="true">&laquo;</span>
                        </Hyperlink>
                        <Hyperlink>1</Hyperlink>
                        <Hyperlink active>2</Hyperlink>
                        <Hyperlink>3</Hyperlink>
                        <Hyperlink label="Next">
                            <span aria-hidden="true">&raquo;</span>
                        </Hyperlink>
                    </Pagination>
                    <Pagination label="Page navigation example" className="justify-content-center">
                        <Hyperlink label="Previous" disabled>
                            <span aria-hidden="true">&laquo;</span>
                        </Hyperlink>
                        <Hyperlink>1</Hyperlink>
                        <Hyperlink active>2</Hyperlink>
                        <Hyperlink>3</Hyperlink>
                        <Hyperlink label="Next">
                            <span aria-hidden="true">&raquo;</span>
                        </Hyperlink>
                    </Pagination>
                    {/** PAGINATION: SIZE */}
                    <Pagination label="Page navigation example" size={Pagination.lg}>
                        <Hyperlink label="Previous" disabled>
                            <span aria-hidden="true">&laquo;</span>
                        </Hyperlink>
                        <Hyperlink>1</Hyperlink>
                        <Hyperlink active>2</Hyperlink>
                        <Hyperlink>3</Hyperlink>
                        <Hyperlink label="Next">
                            <span aria-hidden="true">&raquo;</span>
                        </Hyperlink>
                    </Pagination>
                    <Pagination label="Page navigation example" size={Pagination.sm}>
                        <Hyperlink label="Previous" disabled>
                            <span aria-hidden="true">&laquo;</span>
                        </Hyperlink>
                        <Hyperlink>1</Hyperlink>
                        <Hyperlink active>2</Hyperlink>
                        <Hyperlink>3</Hyperlink>
                        <Hyperlink label="Next">
                            <span aria-hidden="true">&raquo;</span>
                        </Hyperlink>
                    </Pagination>
                    {/** PAGINATION: DISABLED AND ACTIVE STATES */}
                    <Pagination label="Page navigation example">
                        <Hyperlink label="Previous" disabled>
                            <span aria-hidden="true">&laquo;</span>
                        </Hyperlink>
                        <Hyperlink>1</Hyperlink>
                        <Hyperlink active>2</Hyperlink>
                        <Hyperlink>3</Hyperlink>
                        <Hyperlink label="Next">
                            <span aria-hidden="true">&raquo;</span>
                        </Hyperlink>
                    </Pagination>
                    {/** PAGINATION: WORKING WITH ICON */}
                    <Pagination label="Page navigation example">
                        <Hyperlink label="Previous">
                            <span aria-hidden="true">&laquo;</span>
                        </Hyperlink>
                        <Hyperlink>1</Hyperlink>
                        <Hyperlink>2</Hyperlink>
                        <Hyperlink>3</Hyperlink>
                        <Hyperlink label="Next">
                            <span aria-hidden="true">&raquo;</span>
                        </Hyperlink>
                    </Pagination>
                    {/** PAGINATION */}
                    <Pagination>
                        <Hyperlink>Previous</Hyperlink>
                        <Hyperlink>1</Hyperlink>
                        <Hyperlink>2</Hyperlink>
                        <Hyperlink>3</Hyperlink>
                        <Hyperlink>Next</Hyperlink>
                    </Pagination>
                </div>
            </Context.Provider>
        );
    }
}