/**
 * 현재 COMPRESSED_RGBA_S3TC_DXT5_EXT 만 지원합니다.
 * gl.generateMipmap(gl.TEXTURE_2D); 에서 예외가 발생합니다.
 *
 */
export default class Texture
{
    static getTarget(extension, format)
    {
        switch(format)
        {
            case 1146639413: return extension.COMPRESSED_RGBA_S3TC_DXT5_EXT;
            default: throw new Error();
        }
    }
    constructor(name, format)
    {
        this.__name = name;
        this.__format = format;
        this.__id = null;
        this.__mipmaps = [];
    }

    push(o)
    {
        this.__mipmaps.push(o);
    }

    load(application)
    {
        const gl = application.gl;
        const extension = application.extension;
        var ext = (
          gl.getExtension('WEBGL_compressed_texture_s3tc') ||
          gl.getExtension('MOZ_WEBGL_compressed_texture_s3tc') ||
          gl.getExtension('WEBKIT_WEBGL_compressed_texture_s3tc')
        );
        if(!this.__id)
        {
            this.__id = gl.createTexture();
            gl.bindTexture(gl.TEXTURE_2D, this.__id);
            this.__mipmaps.forEach((mipmap, index) => {
                gl.compressedTexImage2D(gl.TEXTURE_2D, index, ext.COMPRESSED_RGBA_S3TC_DXT5_EXT, mipmap.width, mipmap.height, 0, mipmap.data);
            });

            gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
            gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);

            // gl.generateMipmap(gl.TEXTURE_2D);
        }
    }

    unload(application)
    {
        const gl = application.gl;
    }

    get id(){ return this.__id; }
}
