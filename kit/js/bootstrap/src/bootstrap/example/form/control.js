import React, {Component} from 'react';

import Form from '../../components/form';
import Label from '../../components/label';
import Input from '../../components/input';
import Button from '../../components/button';

import Contextual from '../../contextual';
import Context from '../../context';

export default class ExampleFormControlView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** FORM: DATALIST (DEFAULT VALUE PROBLEM*/}
                    {<Form>
                        <Label htmlFor="exampleDataList">Datalist example</Label>
                        <Input list="datalistOptions" id="exampleDataList" placeholder="Type to search..." defaultValue=""></Input>
                        <datalist id="datalistOptions">
                            <option value="San Francisco" />
                            <option value="New York" />
                            <option value="Seattle" />
                            <option value="Los Angeles" />
                            <option value="Chicago" />
                        </datalist>
                    </Form>}
                    {/** FORM COLOR */}
                    <Form>
                        <Label htmlFor="exampleColorInput">Color picker</Label>
                        <Input type="color" defaultValue="#563d7c" title="Choose your color" />
                    </Form>
                    {/** FILE INPUT */}
                    <Form>
                        <div className="mb-3">
                            <Label htmlFor="formFile">Default file input example</Label>
                            <Input type="file" id="formFile" />
                        </div>
                        <div className="mb-3">
                            <Label htmlFor="formFile">Multiple file input example</Label>
                            <Input type="file" id="formFile2" multiple />
                        </div>
                        <div className="mb-3">
                            <Label htmlFor="formFile">Default file input example</Label>
                            <Input type="file" id="formFile3" disabled />
                        </div>
                        <div className="mb-3">
                            <Label htmlFor="formFile">Default file input example</Label>
                            <Input type="file" id="formFile5" disabled size={Input.sm} />
                        </div>
                        <div className="mb-3">
                            <Label htmlFor="formFile">Default file input example</Label>
                            <Input type="file" id="formFile4" disabled size={Input.lg} />
                        </div>
                    </Form>
                    {/** FORM CONTROL: CONFIRM IDENTITY */}
                    <Form className="row g-3">
                        <div className="col-auto">
                            <Label htmlFor="staticEmail2" className="visually-hidden">Email</Label>
                            <Input type="text" readOnly plaintext id="staticEmail2" value="email@example.com"></Input>
                        </div>
                        <div className="col-auto">
                            <Label htmlFor="inputPassword2" className="visually-hidden">Password</Label>
                            <Input type="password" id="inputPassword2" placeholder="Password"></Input>
                        </div>
                        <div className="col-auto">
                            <Button type="submit" className="mb-3" contextual={Contextual.primary}>Confirm identity</Button>
                        </div>
                    </Form>
                    {/** FORM CONTROL: READONLY PLAIN TEXT */}
                    <Form>
                        <div className="mb-3 row">
                            <Label htmlFor="staticEmail" className="col-sm-2 col-form-label">Email</Label>
                            <div className="col-sm-10">
                                <Input type="text" readOnly plaintext id="staticEmail" value="email@example.com"></Input>
                            </div>
                        </div>
                        <div className="mb-3 row">
                            <Label htmlFor="inputPassword" className="col-sm-2 col-form-label">Password</Label>
                            <div className="col-sm-10">
                                <Input type="password" id="inputPassword" />
                            </div>
                        </div>
                    </Form>
                    {/** FORM CONTROL: SIZE & DISABLED READONLY */}
                    <Form>
                        <Input size={Input.lg} type="text" placeholder=".form-control-lg" aria-label=".form-control-lg example" />
                        <Input type="text" placeholder="Default input" aria-label="default input example" />
                        <Input size={Input.sm} type="text" placeholder=".form-control-sm" aria-label=".form-control-sm example" />
                        <Input type="text" placeholder="Disabled input" aria-label="Disabled input example" disabled />
                        <Input type="text" placeholder="Disabled readonly input" aria-label="Disabled input example" disabled readOnly />
                        <Input type="text" placeholder="Readonly input" aria-label="Readonly input example" readOnly />
                    </Form>
                    {/** FORM CONTROL */}
                    <Form>
                        <div className="mb-3">
                            <Label htmlFor="exampleFormControlInput1">Email address</Label>
                            <Input type="email" id="exampleFormControlInput1" placeholder="name@example.com"></Input>
                        </div>
                        <div className="mb-3">
                            <Label htmlFor="exampleFormControlTextarea1">Email textarea</Label>
                            <textarea className="form-control" id="exampleFormControlTextarea1" rows="3"></textarea>
                        </div>
                    </Form>
                </div>
            </Context.Provider>
        );
    }
}

