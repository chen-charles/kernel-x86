klib_ad
======

overview
-----------
*klib_ad* component of *klib* implements required definitions from *klib_sl* which defines a HAL layer.  
*klib_ad* is also providing platform-specific definitions with their declarations, such as sysenter/syscall.  
*klib_ad* *must* provides a final include file (with the name of the specific platform) that provides ALL definitions required by *klib_sl*  

