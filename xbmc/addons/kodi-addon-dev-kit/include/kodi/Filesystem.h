/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "AddonBase.h"

#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
#include <map>
#include <vector>
#endif /* __cplusplus */

#ifdef _WIN32 // windows
#ifndef _SSIZE_T_DEFINED
typedef intptr_t ssize_t;
#define _SSIZE_T_DEFINED
#endif // !_SSIZE_T_DEFINED
#endif

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  //¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
  // "C" Definitions, structures and enumerators of filesystem
  //{{{

  //============================================================================
  /// @defgroup cpp_kodi_vfs_Defs_OpenFileFlags enum OpenFileFlags
  /// @ingroup cpp_kodi_vfs_Defs
  /// @brief **Flags to define way how file becomes opened**\n
  /// The values can be used together, e.g. <b>`file.Open("myfile", READ_TRUNCATED | READ_CHUNKED);`</b>
  ///
  /// Used on @ref kodi::vfs::CFile::OpenFile().
  ///
  //@{
  typedef enum OpenFileFlags
  {
    /// @brief Indicate that caller can handle truncated reads, where function
    /// returns before entire buffer has been filled.
    READ_TRUNCATED = 0x01,

    /// @brief Indicate that that caller support read in the minimum defined
    /// chunk size, this disables internal cache then.
    READ_CHUNKED = 0x02,

    /// @brief Use cache to access this file.
    READ_CACHED = 0x04,

    /// @brief Open without caching. regardless to file type.
    READ_NO_CACHE = 0x08,

    /// @brief Calcuate bitrate for file while reading.
    READ_BITRATE = 0x10,

    /// @brief Indicate to the caller we will seek between multiple streams in
    /// the file frequently.
    READ_MULTI_STREAM = 0x20,

    /// @brief indicate to the caller file is audio and/or video (and e.g. may
    /// grow).
    READ_AUDIO_VIDEO = 0x40,

    /// @brief Indicate that caller will do write operations before reading.
    READ_AFTER_WRITE = 0x80,

    /// @brief Indicate that caller want to reopen a file if its already open.
    READ_REOPEN = 0x100
  } OpenFileFlags;
  //@}
  //----------------------------------------------------------------------------

  //============================================================================
  /// @defgroup cpp_kodi_vfs_Defs_CURLOptiontype enum CURLOptiontype
  /// @ingroup cpp_kodi_vfs_Defs
  /// @brief **CURL message types**\n
  /// Used on kodi::vfs::CFile::CURLAddOption().
  ///
  //@{
  typedef enum CURLOptiontype
  {
    /// @brief Set a general option.
    ADDON_CURL_OPTION_OPTION,

    /// @brief Set a protocol option.
    ///
    /// The following names for *ADDON_CURL_OPTION_PROTOCOL* are possible:
    ///
    /// | Option name                         | Description
    /// |------------------------------------:|:--------------------------------
    /// | <b>`accept-charset`</b>             | Set the "accept-charset" header
    /// | <b>`acceptencoding or encoding`</b> | Set the "accept-encoding" header
    /// | <b>`active-remote`</b>              | Set the "active-remote" header
    /// | <b>`auth`</b>                       | Set the authentication method. Possible values: any, anysafe, digest, ntlm
    /// | <b>`connection-timeout`</b>         | Set the connection timeout in seconds
    /// | <b>`cookie`</b>                     | Set the "cookie" header
    /// | <b>`customrequest`</b>              | Set a custom HTTP request like DELETE
    /// | <b>`noshout`</b>                    | Set to true if kodi detects a stream as shoutcast by mistake.
    /// | <b>`postdata`</b>                   | Set the post body (value needs to be base64 encoded). (Implicitly sets the request to POST)
    /// | <b>`referer`</b>                    | Set the "referer" header
    /// | <b>`user-agent`</b>                 | Set the "user-agent" header
    /// | <b>`seekable`</b>                   | Set the stream seekable. 1: enable, 0: disable
    /// | <b>`sslcipherlist`</b>              | Set list of accepted SSL ciphers.
    ///
    ADDON_CURL_OPTION_PROTOCOL,

    /// @brief Set User and password
    ADDON_CURL_OPTION_CREDENTIALS,

    /// @brief Add a Header
    ADDON_CURL_OPTION_HEADER
  } CURLOptiontype;
  //@}
  //----------------------------------------------------------------------------

  //============================================================================
  /// @defgroup cpp_kodi_vfs_Defs_FilePropertyTypes enum FilePropertyTypes
  /// @ingroup cpp_kodi_vfs_Defs
  /// @brief **File property types**\n
  /// Mostly to read internet sources.
  ///
  /// Used on kodi::vfs::CFile::GetPropertyValue() and kodi::vfs::CFile::GetPropertyValues().
  ///
  //@{
  typedef enum FilePropertyTypes
  {
    /// @brief Get protocol response line.
    ADDON_FILE_PROPERTY_RESPONSE_PROTOCOL,
    /// @brief Get a response header.
    ADDON_FILE_PROPERTY_RESPONSE_HEADER,
    /// @brief Get file content type.
    ADDON_FILE_PROPERTY_CONTENT_TYPE,
    /// @brief Get file content charset.
    ADDON_FILE_PROPERTY_CONTENT_CHARSET,
    /// @brief Get file mime type.
    ADDON_FILE_PROPERTY_MIME_TYPE,
    /// @brief Get file effective URL (last one if redirected).
    ADDON_FILE_PROPERTY_EFFECTIVE_URL
  } FilePropertyTypes;
  //@}
  //----------------------------------------------------------------------------

  //}}}

  //¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
  // "C" Internal interface tables for intercommunications between addon and kodi
  //{{{

  struct STAT_STRUCTURE
  {
    /// ID of device containing file
    uint32_t deviceId;
    /// Total size, in bytes
    uint64_t size;
    /// Time of last access
    time_t accessTime;
    /// Time of last modification
    time_t modificationTime;
    /// Time of last status change
    time_t statusTime;
    /// The stat url is a directory
    bool isDirectory;
    /// The stat url is a symbolic link
    bool isSymLink;
  };

  struct VFSProperty
  {
    char* name;
    char* val;
  };

  struct VFSDirEntry
  {
    char* label; //!< item label
    char* title; //!< item title
    char* path; //!< item path
    unsigned int num_props; //!< Number of properties attached to item
    struct VFSProperty* properties; //!< Properties
    time_t date_time; //!< file creation date & time
    bool folder; //!< Item is a folder
    uint64_t size; //!< Size of file represented by item
  };

  typedef struct AddonToKodiFuncTable_kodi_filesystem
  {
    bool (*can_open_directory)(void* kodiBase, const char* url);
    bool (*create_directory)(void* kodiBase, const char* path);
    bool (*remove_directory)(void* kodiBase, const char* path);
    bool (*directory_exists)(void* kodiBase, const char* path);
    bool (*get_directory)(void* kodiBase,
                          const char* path,
                          const char* mask,
                          struct VFSDirEntry** items,
                          unsigned int* num_items);
    void (*free_directory)(void* kodiBase, struct VFSDirEntry* items, unsigned int num_items);

    bool (*file_exists)(void* kodiBase, const char* filename, bool useCache);
    bool (*stat_file)(void* kodiBase, const char* filename, struct STAT_STRUCTURE* buffer);
    bool (*delete_file)(void* kodiBase, const char* filename);
    bool (*rename_file)(void* kodiBase, const char* filename, const char* newFileName);
    bool (*copy_file)(void* kodiBase, const char* filename, const char* dest);

    char* (*get_file_md5)(void* kodiBase, const char* filename);
    char* (*get_cache_thumb_name)(void* kodiBase, const char* filename);
    char* (*make_legal_filename)(void* kodiBase, const char* filename);
    char* (*make_legal_path)(void* kodiBase, const char* path);
    char* (*translate_special_protocol)(void* kodiBase, const char* strSource);

    void* (*open_file)(void* kodiBase, const char* filename, unsigned int flags);
    void* (*open_file_for_write)(void* kodiBase, const char* filename, bool overwrite);
    ssize_t (*read_file)(void* kodiBase, void* file, void* ptr, size_t size);
    bool (*read_file_string)(void* kodiBase, void* file, char* szLine, int iLineLength);
    ssize_t (*write_file)(void* kodiBase, void* file, const void* ptr, size_t size);
    void (*flush_file)(void* kodiBase, void* file);
    int64_t (*seek_file)(void* kodiBase, void* file, int64_t position, int whence);
    int (*truncate_file)(void* kodiBase, void* file, int64_t size);
    int64_t (*get_file_position)(void* kodiBase, void* file);
    int64_t (*get_file_length)(void* kodiBase, void* file);
    double (*get_file_download_speed)(void* kodiBase, void* file);
    void (*close_file)(void* kodiBase, void* file);
    int (*get_file_chunk_size)(void* kodiBase, void* file);
    char** (*get_property_values)(
        void* kodiBase, void* file, int type, const char* name, int* numValues);

    void* (*curl_create)(void* kodiBase, const char* url);
    bool (*curl_add_option)(
        void* kodiBase, void* file, int type, const char* name, const char* value);
    bool (*curl_open)(void* kodiBase, void* file, unsigned int flags);
  } AddonToKodiFuncTable_kodi_filesystem;

  //}}}

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

//··············································································

#ifdef __cplusplus

namespace kodi
{
namespace vfs
{

//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// Main page text for filesystem group by Doxygen.
//{{{

//==============================================================================
///
/// @defgroup cpp_kodi_vfs  Interface - kodi::vfs
/// @ingroup cpp
/// @brief **Virtual filesystem functions**\n
/// Offers classes and functions for access to the Virtual File Server (VFS)
/// which you can use to manipulate files and folders.
///
/// This system allow the use of ["Special Protocol"](https://kodi.wiki/view/Special_protocol)
/// where is Kodi's solution to platform dependent directories. Common directory
/// names are assigned a <b>`special://[name]`</b> path which is passed around
/// inside Kodi and then translated to the platform specific path before the
/// operating system sees it. This helps keep most of the platform mess
/// centralized in the code.\n
/// To become a correct path back can be @ref TranslateSpecialProtocol() used.
///
/// It has the header @ref Filesystem.h "#include <kodi/Filesystem.h>" be
/// included to enjoy it.
///
//------------------------------------------------------------------------------

//==============================================================================
/// @defgroup cpp_kodi_vfs_Defs Definitions, structures and enumerators
/// @ingroup cpp_kodi_vfs
/// @brief **Virtual file Server definition values**\n
/// All to VFS system functions associated data structures.
///
//------------------------------------------------------------------------------

//==============================================================================
/// @defgroup cpp_kodi_vfs_Directory 1. Directory functions
/// @ingroup cpp_kodi_vfs
/// @brief **Globally available directories related functions**\n
/// Used to perform typical operations with it.
///
//------------------------------------------------------------------------------

//==============================================================================
/// @defgroup cpp_kodi_vfs_File 2. File functions
/// @ingroup cpp_kodi_vfs
/// @brief **Globally available file related functions**\n
/// Used to perform typical operations with it.
///
//------------------------------------------------------------------------------

//==============================================================================
/// @defgroup cpp_kodi_vfs_General 3. General functions
/// @ingroup cpp_kodi_vfs
/// @brief **Other globally available functions**\n
/// Used to perform typical operations with it.
///
//------------------------------------------------------------------------------

//}}}

//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// "C++" related filesystem definitions
//{{{

//==============================================================================
/// @defgroup cpp_kodi_vfs_Defs_FileStatus class FileStatus
/// @ingroup cpp_kodi_vfs_Defs
/// @brief **File information status**\n
/// Used on kodi::vfs::StatFile(), all of these calls return a this stat
/// structure, which contains the following fields:
///
//@{
class FileStatus : public kodi::addon::CStructHdl<FileStatus, STAT_STRUCTURE>
{
public:
  /*! \cond PRIVATE */
  FileStatus() { memset(m_cStructure, 0, sizeof(STAT_STRUCTURE)); }
  FileStatus(const FileStatus& channel) : CStructHdl(channel) {}
  FileStatus(const STAT_STRUCTURE* channel) : CStructHdl(channel) {}
  FileStatus(STAT_STRUCTURE* channel) : CStructHdl(channel) {}
  /*! \endcond */

  /// @defgroup cpp_kodi_vfs_Defs_FileStatus_Help *Value Help*
  /// @ingroup cpp_kodi_vfs_Defs_FileStatus
  /// ----------------------------------------------------------------------------
  ///
  /// <b>The following table contains values that can be set with @ref cpp_kodi_vfs_Defs_FileStatus :</b>
  /// | Name | Type | Set call | Get call
  /// |------|------|----------|----------
  /// | **ID of device containing file** | `uint32_t` | @ref FileStatus::SetDeviceId "SetDeviceId" | @ref FileStatus::GetDeviceId "GetDeviceId"
  /// | **Total size, in bytes** | `uint64_t` | @ref FileStatus::SetSize "SetSize" | @ref FileStatus::GetSize "GetSize"
  /// | **Time of last access** | `time_t` | @ref FileStatus::SetAccessTime "SetAccessTime" | @ref FileStatus::GetAccessTime "GetAccessTime"
  /// | **Time of last modification** | `time_t` | @ref FileStatus::SetModificationTime "SetModificationTime" | @ref FileStatus::GetModificationTime "GetModificationTime"
  /// | **Time of last status change** | `time_t` | @ref FileStatus::SetStatusTime "SetStatusTime" | @ref FileStatus::GetStatusTime "GetStatusTime"
  /// | **Stat url is a directory** | `bool` | @ref FileStatus::SetIsDirectory "SetIsDirectory" | @ref FileStatus::GetIsDirectory "GetIsDirectory"
  /// | **Stat url as a symbolic link** | `bool` | @ref FileStatus::SetIsSymLink "SetIsSymLink" | @ref FileStatus::GetIsSymLink "GetIsSymLink"
  ///

  /// @addtogroup cpp_kodi_vfs_Defs_FileStatus
  /// @copydetails cpp_kodi_vfs_Defs_FileStatus_Help
  //@{

  /// @brief Set ID of device containing file.
  void SetDeviceId(uint32_t deviceId) { m_cStructure->deviceId = deviceId; }

  /// @brief Get ID of device containing file.
  uint32_t GetDeviceId() const { return m_cStructure->deviceId; }

  /// @brief Set total size, in bytes.
  void SetSize(uint64_t size) { m_cStructure->size = size; }

  /// @brief Get total size, in bytes.
  uint64_t GetSize() const { return m_cStructure->size; }

  /// @brief Set time of last access.
  void SetAccessTime(time_t accessTime) { m_cStructure->accessTime = accessTime; }

  /// @brief Get time of last access.
  time_t GetAccessTime() const { return m_cStructure->accessTime; }

  /// @brief Set time of last modification.
  void SetModificationTime(time_t modificationTime)
  {
    m_cStructure->modificationTime = modificationTime;
  }

  /// @brief Get time of last modification.
  time_t GetModificationTime() const { return m_cStructure->modificationTime; }

  /// @brief Set time of last status change.
  void SetStatusTime(time_t statusTime) { m_cStructure->statusTime = statusTime; }

  /// @brief Get time of last status change.
  time_t GetStatusTime() const { return m_cStructure->statusTime; }

  /// @brief Set the stat url is a directory.
  void SetIsDirectory(bool isDirectory) { m_cStructure->isDirectory = isDirectory; }

  /// @brief The stat url is a directory if returns true.
  bool GetIsDirectory() const { return m_cStructure->isDirectory; }

  /// @brief Set stat url as a symbolic link.
  void SetIsSymLink(bool isSymLink) { m_cStructure->isSymLink = isSymLink; }

  /// @brief Get stat url is a symbolic link.
  bool GetIsSymLink() const { return m_cStructure->isSymLink; }

  //@}
};
//@}
//------------------------------------------------------------------------------

//==============================================================================
/// @defgroup cpp_kodi_vfs_CDirEntry class CDirEntry
/// @ingroup cpp_kodi_vfs_Defs
///
/// @brief **Virtual file server directory entry**\n
/// This class is used as an entry for files and folders in
/// kodi::vfs::GetDirectory().
///
///
/// ------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
///
/// ...
///
/// std::vector<kodi::vfs::CDirEntry> items;
/// kodi::vfs::GetDirectory("special://temp", "", items);
///
/// fprintf(stderr, "Directory have %lu entries\n", items.size());
/// for (unsigned long i = 0; i < items.size(); i++)
/// {
///   char buff[20];
///   time_t now = items[i].DateTime();
///   strftime(buff, 20, "%Y-%m-%d %H:%M:%S", gmtime(&now));
///   fprintf(stderr, " - %04lu -- Folder: %s -- Name: %s -- Path: %s -- Time: %s\n",
///             i+1,
///             items[i].IsFolder() ? "yes" : "no ",
///             items[i].Label().c_str(),
///             items[i].Path().c_str(),
///             buff);
/// }
/// ~~~~~~~~~~~~~
///
/// It has the header @ref Filesystem.h "#include <kodi/Filesystem.h>" be included
/// to enjoy it.
///
//@{
class CDirEntry
{
public:
  //============================================================================
  /// @ingroup cpp_kodi_vfs_CDirEntry
  /// @brief Constructor for VFS directory entry
  ///
  /// @param[in] label    [opt] Name to use for entry
  /// @param[in] path     [opt] Used path of the entry
  /// @param[in] folder   [opt] If set entry used as folder
  /// @param[in] size     [opt] If used as file, his size defined there
  /// @param[in] dateTime [opt] Date time of the entry
  ///
  CDirEntry(const std::string& label = "",
            const std::string& path = "",
            bool folder = false,
            int64_t size = -1,
            time_t dateTime = 0)
    : m_label(label), m_path(path), m_folder(folder), m_size(size), m_dateTime(dateTime)
  {
  }
  //----------------------------------------------------------------------------

  //============================================================================
  // @note Not for addon development itself needed, thats why below is
  // disabled for doxygen!
  //
  // @ingroup cpp_kodi_vfs_CDirEntry
  // @brief Constructor to create own copy
  //
  // @param[in] dirEntry pointer to own class type
  //
  explicit CDirEntry(const VFSDirEntry& dirEntry)
    : m_label(dirEntry.label ? dirEntry.label : ""),
      m_path(dirEntry.path ? dirEntry.path : ""),
      m_folder(dirEntry.folder),
      m_size(dirEntry.size),
      m_dateTime(dirEntry.date_time)
  {
  }
  //----------------------------------------------------------------------------

  /// @defgroup cpp_kodi_vfs_CDirEntry_Help *Value Help*
  /// @ingroup cpp_kodi_vfs_CDirEntry
  /// --------------------------------------------------------------------------
  ///
  /// <b>The following table contains values that can be set with @ref cpp_kodi_vfs_CDirEntry :</b>
  /// | Name | Type | Set call | Get call | Clear call |
  /// |------|------|----------|----------|------------|
  /// | **Directory entry name** | `std::string` | @ref CDirEntry::SetLabel "SetLabel" | @ref CDirEntry::Label "Label" | |
  /// | **Title of entry** | `std::string` | @ref CDirEntry::SetTitle "SetTitle" | @ref CDirEntry::Title "Title" | |
  /// | **Path of the entry** | `std::string` | @ref CDirEntry::SetPath "SetPath" | @ref CDirEntry::Path "Path" | |
  /// | **Entry is folder** | `bool` | @ref CDirEntry::SetFolder "SetFolder" | @ref CDirEntry::IsFolder "IsFolder" | |
  /// | **The size of the file** | `int64_t` | @ref CDirEntry::SetSize "SetSize" | @ref CDirEntry::Size "Size" | |
  /// | **File time and date** | `time_t` | @ref CDirEntry::SetDateTime "SetDateTime" | @ref CDirEntry::DateTime "DateTime" | |
  /// | **Property entries** | `std::string, std::string` | @ref CDirEntry::AddProperty "AddProperty" | @ref CDirEntry::GetProperties "GetProperties" | @ref CDirEntry::ClearProperties "ClearProperties"
  ///

  /// @addtogroup cpp_kodi_vfs_CDirEntry
  /// @copydetails cpp_kodi_vfs_CDirEntry_Help
  //@{

  //============================================================================
  /// @brief Get the directory entry name.
  ///
  /// @return Name of the entry
  ///
  const std::string& Label(void) const { return m_label; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @brief Get the optional title of entry.
  ///
  /// @return Title of the entry, if exists
  ///
  const std::string& Title(void) const { return m_title; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @brief Get the path of the entry.
  ///
  /// @return File system path of the entry
  ///
  const std::string& Path(void) const { return m_path; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @brief Used to check entry is folder.
  ///
  /// @return true if entry is a folder
  ///
  bool IsFolder(void) const { return m_folder; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @brief If file, the size of the file.
  ///
  /// @return Defined file size
  ///
  int64_t Size(void) const { return m_size; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @brief Get file time and date for a new entry.
  ///
  /// @return The with time_t defined date and time of file
  ///
  time_t DateTime() { return m_dateTime; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @brief Set the label name.
  ///
  /// @param[in] label name of entry
  ///
  void SetLabel(const std::string& label) { m_label = label; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @brief Set the title name.
  ///
  /// @param[in] title title name of entry
  ///
  void SetTitle(const std::string& title) { m_title = title; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @brief Set the path of the entry.
  ///
  /// @param[in] path path of entry
  ///
  void SetPath(const std::string& path) { m_path = path; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @brief Set the entry defined as folder.
  ///
  /// @param[in] folder If true becomes entry defined as folder
  ///
  void SetFolder(bool folder) { m_folder = folder; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @brief Set a file size for a new entry.
  ///
  /// @param[in] size Size to set for dir entry
  ///
  void SetSize(int64_t size) { m_size = size; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @brief Set file time and date for a new entry.
  ///
  /// @param[in] dateTime The with time_t defined date and time of file
  ///
  void SetDateTime(time_t dateTime) { m_dateTime = dateTime; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @brief Add a by string defined property entry to directory entry.
  ///
  /// @note A property can be used to add some special information about a file
  /// or directory entry, this can be used on other places to do the right work
  /// of them.
  ///
  /// @param[in] id     Identification name of property
  /// @param[in] value  The property value to add by given id
  ///
  void AddProperty(const std::string& id, const std::string& value) { m_properties[id] = value; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @brief Clear all present properties.
  ///
  void ClearProperties() { m_properties.clear(); }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @brief Get the present properties list on directory entry.
  ///
  /// @return map with all present properties
  ///
  const std::map<std::string, std::string>& GetProperties() const { return m_properties; }
  //----------------------------------------------------------------------------

  //@}

private:
  std::string m_label;
  std::string m_title;
  std::string m_path;
  std::map<std::string, std::string> m_properties;
  bool m_folder;
  int64_t m_size;
  time_t m_dateTime;
};
//@}
//------------------------------------------------------------------------------

//}}}

//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// "C++" Directory related functions
//{{{

//==============================================================================
/// @ingroup cpp_kodi_vfs_Directory
/// @brief Make a directory.
///
/// The kodi::vfs::CreateDirectory() function shall create a
/// new directory with name path.
///
/// The newly created directory shall be an empty directory.
///
/// @param[in] path Path to the directory.
/// @return Upon successful completion, CreateDirectory() shall return true.
///         Otherwise false shall be returned, no directory shall be created.
///
///
/// -------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
/// ...
/// std::string directory = "C:\\my_dir";
/// bool ret = kodi::vfs::CreateDirectory(directory);
/// fprintf(stderr, "Directory '%s' successfull created: %s\n", directory.c_str(), ret ? "yes" : "no");
/// ...
/// ~~~~~~~~~~~~~
///
inline bool CreateDirectory(const std::string& path)
{
  using namespace kodi::addon;

  return CAddonBase::m_interface->toKodi->kodi_filesystem->create_directory(
      CAddonBase::m_interface->toKodi->kodiBase, path.c_str());
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_kodi_vfs_Directory
/// @brief Verifying the Existence of a Directory.
///
/// The kodi::vfs::DirectoryExists() method determines whether
/// a specified folder exists.
///
/// @param[in] path Path to the directory.
/// @return True when it exists, false otherwise.
///
///
/// -------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
/// ...
/// std::string directory = "C:\\my_dir";
/// bool ret = kodi::vfs::DirectoryExists(directory);
/// fprintf(stderr, "Directory '%s' present: %s\n", directory.c_str(), ret ? "yes" : "no");
/// ...
/// ~~~~~~~~~~~~~
///
inline bool DirectoryExists(const std::string& path)
{
  using namespace kodi::addon;

  return CAddonBase::m_interface->toKodi->kodi_filesystem->directory_exists(
      CAddonBase::m_interface->toKodi->kodiBase, path.c_str());
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_kodi_vfs_Directory
/// @brief Removes a directory.
///
/// The kodi::vfs::RemoveDirectory() function shall remove a
/// directory whose name is given by path.
///
/// @param[in] path Path to the directory.
/// @return Upon successful completion, the function RemoveDirectory() shall
///         return true. Otherwise, false shall be returned, and errno set
///         to indicate the error. If false is returned, the named directory
///         shall not be changed.
///
///
/// -------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
/// ...
/// bool ret = kodi::vfs::RemoveDirectory("C:\\my_dir");
/// ...
/// ~~~~~~~~~~~~~
///
inline bool RemoveDirectory(const std::string& path)
{
  using namespace kodi::addon;

  return CAddonBase::m_interface->toKodi->kodi_filesystem->remove_directory(
      CAddonBase::m_interface->toKodi->kodiBase, path.c_str());
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_kodi_vfs_Directory
/// @brief Lists a directory.
///
/// Return the list of files and directories which have been found in the
/// specified directory and which respect the given constraint.
///
/// It can handle the normal OS dependent paths and also the special virtual
/// filesystem from Kodi what starts with \b special://.
///
/// @param[in]  path  The path in which the files and directories are located.
/// @param[in]  mask  Mask to filter out requested files, e.g. "*.avi|*.mpg" to
///                   files with this ending.
/// @param[out] items The returned list directory entries.
/// @return           True if listing was successful, false otherwise.
///
///
/// -------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
///
/// std::vector<kodi::vfs::CDirEntry> items;
/// kodi::vfs::GetDirectory("special://temp", "", items);
///
/// fprintf(stderr, "Directory have %lu entries\n", items.size());
/// for (unsigned long i = 0; i < items.size(); i++)
/// {
///   fprintf(stderr, " - %04lu -- Folder: %s -- Name: %s -- Path: %s\n",
///             i+1,
///             items[i].IsFolder() ? "yes" : "no ",
///             items[i].Label().c_str(),
///             items[i].Path().c_str());
/// }
/// ~~~~~~~~~~~~~
inline bool GetDirectory(const std::string& path,
                         const std::string& mask,
                         std::vector<kodi::vfs::CDirEntry>& items)
{
  using namespace kodi::addon;

  VFSDirEntry* dir_list = nullptr;
  unsigned int num_items = 0;
  if (CAddonBase::m_interface->toKodi->kodi_filesystem->get_directory(
          CAddonBase::m_interface->toKodi->kodiBase, path.c_str(), mask.c_str(), &dir_list,
          &num_items))
  {
    if (dir_list)
    {
      for (unsigned int i = 0; i < num_items; ++i)
        items.emplace_back(dir_list[i]);

      CAddonBase::m_interface->toKodi->kodi_filesystem->free_directory(
          CAddonBase::m_interface->toKodi->kodiBase, dir_list, num_items);
    }

    return true;
  }
  return false;
}
//------------------------------------------------------------------------------

//}}}

//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// "C++" File related functions
//{{{

//==============================================================================
/// @ingroup cpp_kodi_vfs_File
/// @brief Check if a file exists.
///
/// @param[in] filename The filename to check.
/// @param[in] usecache Check in file cache.
/// @return true if the file exists false otherwise.
///
///
/// -------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
/// ...
/// bool exists = kodi::vfs::FileExists("special://temp/kodi.log");
/// fprintf(stderr, "Log file should be always present, is it present? %s\n", exists ? "yes" : "no");
/// ~~~~~~~~~~~~~
///
inline bool FileExists(const std::string& filename, bool usecache = false)
{
  using namespace kodi::addon;

  return CAddonBase::m_interface->toKodi->kodi_filesystem->file_exists(
      CAddonBase::m_interface->toKodi->kodiBase, filename.c_str(), usecache);
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_kodi_vfs_File
/// @brief Get file status.
///
/// These function return information about a file. Execute (search)
/// permission is required on all of the directories in path that
/// lead to the file.
///
/// The call return a stat structure, which contains the on
/// @ref cpp_kodi_vfs_Defs_FileStatus defined values.
///
/// @warning Not all of the OS file systems implement all of the time fields.
///
/// @param[in] filename The filename to read the status from.
/// @param[out] buffer The file status is written into this buffer.
/// @return On success, trur is returned. On error, false is returned
///
///
/// -------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
/// ...
/// kodi::vfs::FileStatus statFile;
/// int ret = kodi::vfs::StatFile("special://temp/kodi.log", statFile);
/// fprintf(stderr, "deviceId (ID of device containing file)       = %u\n"
///                 "size (total size, in bytes)                   = %lu\n"
///                 "accessTime (time of last access)              = %lu\n"
///                 "modificationTime (time of last modification)  = %lu\n"
///                 "statusTime (time of last status change)       = %lu\n"
///                 "isDirectory (The stat url is a directory)     = %s\n"
///                 "isSymLink (The stat url is a symbolic link)   = %s\n"
///                 "Return value                                  = %i\n",
///                      statFile.GetDeviceId(),
///                      statFile.GetSize(),
///                      statFile.GetAccessTime(),
///                      statFile.GetModificationTime(),
///                      statFile.GetStatusTime(),
///                      statFile.GetIsDirectory() ? "true" : "false",
///                      statFile.GetIsSymLink() ? "true" : "false",
///                      ret);
/// ~~~~~~~~~~~~~
///
inline bool StatFile(const std::string& filename, kodi::vfs::FileStatus& buffer)
{
  using namespace kodi::addon;

  return CAddonBase::m_interface->toKodi->kodi_filesystem->stat_file(
      CAddonBase::m_interface->toKodi->kodiBase, filename.c_str(), buffer);
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_kodi_vfs_File
/// @brief Deletes a file.
///
/// @param[in] filename The filename to delete.
/// @return The file was successfully deleted.
///
///
/// -------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
/// #include <kodi/gui/DialogFileBrowser.h>
/// #include <kodi/gui/DialogOK.h>
/// ...
/// std::string filename;
/// if (kodi::gui::DialogFileBrowser::ShowAndGetFile("local", "",
///                                                  "Test File selection and delete of them!",
///                                                  filename))
/// {
///   bool successed = kodi::vfs::DeleteFile(filename);
///   if (!successed)
///     kodi::gui::DialogOK::ShowAndGetInput("Error", "Delete of File", filename, "failed!");
///   else
///     kodi::gui::DialogOK::ShowAndGetInput("Information", "Delete of File", filename, "successfull done.");
/// }
/// ~~~~~~~~~~~~~
///
inline bool DeleteFile(const std::string& filename)
{
  using namespace kodi::addon;

  return CAddonBase::m_interface->toKodi->kodi_filesystem->delete_file(
      CAddonBase::m_interface->toKodi->kodiBase, filename.c_str());
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_kodi_vfs_File
/// @brief Rename a file name.
///
/// @param[in] filename The filename to copy.
/// @param[in] newFileName The new filename
/// @return true if successfully renamed
///
///
inline bool RenameFile(const std::string& filename, const std::string& newFileName)
{
  using namespace kodi::addon;

  return CAddonBase::m_interface->toKodi->kodi_filesystem->rename_file(
      CAddonBase::m_interface->toKodi->kodiBase, filename.c_str(), newFileName.c_str());
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_kodi_vfs_File
/// @brief Copy a file from source to destination.
///
/// @param[in] filename The filename to copy.
/// @param[in] destination The destination to copy file to
/// @return true if successfully copied
///
///
inline bool CopyFile(const std::string& filename, const std::string& destination)
{
  using namespace kodi::addon;

  return CAddonBase::m_interface->toKodi->kodi_filesystem->copy_file(
      CAddonBase::m_interface->toKodi->kodiBase, filename.c_str(), destination.c_str());
}
//------------------------------------------------------------------------------

//}}}

//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// "C++" General filesystem functions
//{{{

//==============================================================================
/// @ingroup cpp_kodi_vfs_General
/// @brief Retrieve MD5sum of a file.
///
/// @param[in] path Path to the file to MD5sum
/// @return MD5 sum of the file
///
///
/// -------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
/// #include <kodi/gui/DialogFileBrowser.h>
/// ...
/// std::string md5;
/// std::string filename;
/// if (kodi::gui::DialogFileBrowser::ShowAndGetFile("local", "*.avi|*.mpg|*.mp4",
///                                                "Test File selection to get MD5",
///                                                filename))
/// {
///   md5 = kodi::vfs::GetFileMD5(filename);
///   fprintf(stderr, "MD5 of file '%s' is %s\n", md5.c_str(), filename.c_str());
/// }
/// ~~~~~~~~~~~~~
///
inline std::string GetFileMD5(const std::string& path)
{
  using namespace kodi::addon;

  std::string strReturn;
  char* strMd5 = CAddonBase::m_interface->toKodi->kodi_filesystem->get_file_md5(
      CAddonBase::m_interface->toKodi->kodiBase, path.c_str());
  if (strMd5 != nullptr)
  {
    if (std::strlen(strMd5))
      strReturn = strMd5;
    CAddonBase::m_interface->toKodi->free_string(CAddonBase::m_interface->toKodi->kodiBase, strMd5);
  }
  return strReturn;
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_kodi_vfs_General
/// @brief Returns a thumb cache filename.
///
/// @param[in] filename Path to file
/// @return Cache filename
///
///
/// ------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
/// #include <kodi/gui/DialogFileBrowser.h>
/// ...
/// std::string thumb;
/// std::string filename;
/// if (kodi::gui::DialogFileBrowser::ShowAndGetFile("local", "*.avi|*.mpg|*.mp4",
///                                                "Test File selection to get Thumnail",
///                                                filename))
/// {
///   thumb = kodi::vfs::GetCacheThumbName(filename);
///   fprintf(stderr, "Thumb name of file '%s' is %s\n", thumb.c_str(), filename.c_str());
/// }
/// ~~~~~~~~~~~~~
///
inline std::string GetCacheThumbName(const std::string& filename)
{
  using namespace kodi::addon;

  std::string strReturn;
  char* strThumbName = CAddonBase::m_interface->toKodi->kodi_filesystem->get_cache_thumb_name(
      CAddonBase::m_interface->toKodi->kodiBase, filename.c_str());
  if (strThumbName != nullptr)
  {
    if (std::strlen(strThumbName))
      strReturn = strThumbName;
    CAddonBase::m_interface->toKodi->free_string(CAddonBase::m_interface->toKodi->kodiBase,
                                                 strThumbName);
  }
  return strReturn;
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_kodi_vfs_General
/// @brief Make filename valid.
///
/// Function to replace not valid characters with '_'. It can be also
/// compared with original before in a own loop until it is equal
/// (no invalid characters).
///
/// @param[in] filename Filename to check and fix
/// @return The legal filename
///
///
/// ------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
/// ...
/// std::string fileName = "///\\jk???lj????.mpg";
/// std::string legalName = kodi::vfs::MakeLegalFileName(fileName);
/// fprintf(stderr, "Legal name of '%s' is '%s'\n", fileName.c_str(), legalName.c_str());
///
/// /* Returns as legal: 'jk___lj____.mpg' */
/// ~~~~~~~~~~~~~
///
inline std::string MakeLegalFileName(const std::string& filename)
{
  using namespace kodi::addon;

  std::string strReturn;
  char* strLegalFileName = CAddonBase::m_interface->toKodi->kodi_filesystem->make_legal_filename(
      CAddonBase::m_interface->toKodi->kodiBase, filename.c_str());
  if (strLegalFileName != nullptr)
  {
    if (std::strlen(strLegalFileName))
      strReturn = strLegalFileName;
    CAddonBase::m_interface->toKodi->free_string(CAddonBase::m_interface->toKodi->kodiBase,
                                                 strLegalFileName);
  }
  return strReturn;
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_kodi_vfs_General
/// @brief Make directory name valid.
///
/// Function to replace not valid characters with '_'. It can be also
/// compared with original before in a own loop until it is equal
/// (no invalid characters).
///
/// @param[in] path Directory name to check and fix
/// @return The legal directory name
///
///
/// ------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
/// ...
/// std::string path = "///\\jk???lj????\\hgjkg";
/// std::string legalPath = kodi::vfs::MakeLegalPath(path);
/// fprintf(stderr, "Legal name of '%s' is '%s'\n", path.c_str(), legalPath.c_str());
///
/// /* Returns as legal: '/jk___lj____/hgjkg' */
/// ~~~~~~~~~~~~~
///
inline std::string MakeLegalPath(const std::string& path)
{
  using namespace kodi::addon;

  std::string strReturn;
  char* strLegalPath = CAddonBase::m_interface->toKodi->kodi_filesystem->make_legal_path(
      CAddonBase::m_interface->toKodi->kodiBase, path.c_str());
  if (strLegalPath != nullptr)
  {
    if (std::strlen(strLegalPath))
      strReturn = strLegalPath;
    CAddonBase::m_interface->toKodi->free_string(CAddonBase::m_interface->toKodi->kodiBase,
                                                 strLegalPath);
  }
  return strReturn;
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_kodi_vfs_General
/// @brief Returns the translated path.
///
/// @param[in] source String or unicode - Path to format
/// @return A human-readable string suitable for logging
///
/// @note Only useful if you are coding for both Linux and Windows. e.g.
/// Converts 'special://masterprofile/script_data' ->
/// '/home/user/.kodi/UserData/script_data' on Linux.
///
///
/// ------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
/// ...
/// std::string path = kodi::vfs::TranslateSpecialProtocol("special://masterprofile/script_data");
/// fprintf(stderr, "Translated path is: %s\n", path.c_str());
/// ...
/// ~~~~~~~~~~~~~
/// or
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
/// ...
/// fprintf(stderr, "Directory 'special://temp' is '%s'\n", kodi::vfs::TranslateSpecialProtocol("special://temp").c_str());
/// ...
/// ~~~~~~~~~~~~~
///
inline std::string TranslateSpecialProtocol(const std::string& source)
{
  using namespace kodi::addon;

  std::string strReturn;
  char* protocol = CAddonBase::m_interface->toKodi->kodi_filesystem->translate_special_protocol(
      CAddonBase::m_interface->toKodi->kodiBase, source.c_str());
  if (protocol != nullptr)
  {
    if (std::strlen(protocol))
      strReturn = protocol;
    CAddonBase::m_interface->toKodi->free_string(CAddonBase::m_interface->toKodi->kodiBase,
                                                 protocol);
  }
  return strReturn;
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_kodi_vfs_General
/// @brief Return the file name from given complate path string.
///
/// @param[in] path The complete path include file and directory
/// @return Filename from path
///
///
/// ------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
/// ...
/// std::string fileName = kodi::vfs::GetFileName("special://temp/kodi.log");
/// fprintf(stderr, "File name is '%s'\n", fileName.c_str());
/// ~~~~~~~~~~~~~
///
inline std::string GetFileName(const std::string& path)
{
  /* find the last slash */
  const size_t slash = path.find_last_of("/\\");
  return path.substr(slash + 1);
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_kodi_vfs_General
/// @brief Return the directory name from given complate path string.
///
/// @param[in] path The complete path include file and directory
/// @return Directory name from path
///
///
/// ------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
/// ...
/// std::string dirName = kodi::vfs::GetDirectoryName("special://temp/kodi.log");
/// fprintf(stderr, "Directory name is '%s'\n", dirName.c_str());
/// ~~~~~~~~~~~~~
///
inline std::string GetDirectoryName(const std::string& path)
{
  // Will from a full filename return the directory the file resides in.
  // Keeps the final slash at end and possible |option=foo options.

  size_t iPosSlash = path.find_last_of("/\\");
  if (iPosSlash == std::string::npos)
    return ""; // No slash, so no path (ignore any options)

  size_t iPosBar = path.rfind('|');
  if (iPosBar == std::string::npos)
    return path.substr(0, iPosSlash + 1); // Only path

  return path.substr(0, iPosSlash + 1) + path.substr(iPosBar); // Path + options
}
//------------------------------------------------------------------------------


//==============================================================================
/// @ingroup cpp_kodi_vfs_General
/// @brief Remove the slash on given path name.
///
/// @param[in,out] path The complete path
///
///
/// ------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
/// ...
/// std::string dirName = "special://temp/";
/// kodi::vfs::RemoveSlashAtEnd(dirName);
/// fprintf(stderr, "Directory name is '%s'\n", dirName.c_str());
/// ~~~~~~~~~~~~~
///
inline void RemoveSlashAtEnd(std::string& path)
{
  if (!path.empty())
  {
    char last = path[path.size() - 1];
    if (last == '/' || last == '\\')
      path.erase(path.size() - 1);
  }
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_kodi_vfs_General
/// @brief Return a size aligned to the chunk size at least as large as the
/// chunk size.
///
/// @param[in] chunk The chunk size
/// @param[in] minimum The minimum size (or maybe the minimum number of chunks?)
/// @return The aligned size
///
inline unsigned int GetChunkSize(unsigned int chunk, unsigned int minimum)
{
  if (chunk)
    return chunk * ((minimum + chunk - 1) / chunk);
  else
    return minimum;
}
//------------------------------------------------------------------------------

//}}}

//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// "C++" CFile class
//{{{

//==============================================================================
/// @defgroup cpp_kodi_vfs_CFile 4. class CFile
/// @ingroup cpp_kodi_vfs
///
/// @brief **Creatable class for virtual file server control**\n
/// To perform file read/write with Kodi's filesystem parts.
///
/// CFile is the class used for handling Files in Kodi. This class can be used
/// for creating, reading, writing and modifying files. It directly provides unbuffered, binary disk input/output services
///
/// It has the header @ref Filesystem.h "#include <kodi/Filesystem.h>" be included
/// to enjoy it.
///
///
/// ------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <kodi/Filesystem.h>
///
/// ...
///
/// /* Create the needed file handle class */
/// kodi::vfs::CFile myFile();
///
/// /* In this example we use the user path for the add-on */
/// std::string file = kodi::GetUserPath() + "/myFile.txt";
///
/// /* Now create and open the file or overwrite if present */
/// myFile.OpenFileForWrite(file, true);
///
/// const char* str = "I love Kodi!";
///
/// /* write string */
/// myFile.Write(str, sizeof(str));
///
/// /* On this way the Close() is not needed to call, becomes done from destructor */
///
/// ~~~~~~~~~~~~~
///
//@{
class CFile
{
public:
  //============================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Construct a new, unopened file.
  ///
  CFile() = default;
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief <b>`Close()`</b> is called from the destructor, so explicitly
  /// closing the file isn't required.
  ///
  virtual ~CFile() { Close(); }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Open the file with filename via Kodi's @ref cpp_kodi_vfs_CFile
  /// "CFile". Needs to be closed by calling Close() when done.
  ///
  /// @param[in] filename The filename to open.
  /// @param[in] flags [opt] The flags to pass, see @ref OpenFileFlags
  /// @return True on success or false on failure
  ///
  bool OpenFile(const std::string& filename, unsigned int flags = 0)
  {
    using namespace kodi::addon;

    Close();
    m_file = CAddonBase::m_interface->toKodi->kodi_filesystem->open_file(
        CAddonBase::m_interface->toKodi->kodiBase, filename.c_str(), flags);
    return m_file != nullptr;
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Open the file with filename via Kodi's @ref cpp_kodi_vfs_CFile
  /// "CFile" in write mode. Needs to be closed by calling Close() when
  /// done.
  ///
  /// @note Related folders becomes created if not present.
  ///
  /// @param[in] filename The filename to open.
  /// @param[in] overwrite True to overwrite, false otherwise.
  /// @return True on success or false on failure
  ///
  bool OpenFileForWrite(const std::string& filename, bool overwrite = false)
  {
    using namespace kodi::addon;

    Close();

    // Try to open the file. If it fails, check if we need to create the directory first
    // This way we avoid checking if the directory exists every time
    m_file = CAddonBase::m_interface->toKodi->kodi_filesystem->open_file_for_write(
        CAddonBase::m_interface->toKodi->kodiBase, filename.c_str(), overwrite);
    if (!m_file)
    {
      std::string cacheDirectory = kodi::vfs::GetDirectoryName(filename);
      if (CAddonBase::m_interface->toKodi->kodi_filesystem->directory_exists(
              CAddonBase::m_interface->toKodi->kodiBase, cacheDirectory.c_str()) ||
          CAddonBase::m_interface->toKodi->kodi_filesystem->create_directory(
              CAddonBase::m_interface->toKodi->kodiBase, cacheDirectory.c_str()))
        m_file = CAddonBase::m_interface->toKodi->kodi_filesystem->open_file_for_write(
            CAddonBase::m_interface->toKodi->kodiBase, filename.c_str(), overwrite);
    }
    return m_file != nullptr;
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Check file is opened.
  ///
  /// @return True on open or false on closed or failure
  ///
  bool IsOpen() { return m_file != nullptr; }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Close an open file.
  ///
  void Close()
  {
    using namespace kodi::addon;

    if (!m_file)
      return;
    CAddonBase::m_interface->toKodi->kodi_filesystem->close_file(
        CAddonBase::m_interface->toKodi->kodiBase, m_file);
    m_file = nullptr;
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Create a Curl representation
  ///
  /// @param[in] url The URL of the Type.
  /// @return True on success or false on failure
  ///
  bool CURLCreate(const std::string& url)
  {
    using namespace kodi::addon;

    m_file = CAddonBase::m_interface->toKodi->kodi_filesystem->curl_create(
        CAddonBase::m_interface->toKodi->kodiBase, url.c_str());
    return m_file != nullptr;
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Add options to the curl file created with CURLCreate.
  ///
  /// @param[in] type Option type to set, see @ref CURLOptiontype
  /// @param[in] name Name of the option
  /// @param[in] value Value of the option
  /// @return True on success or false on failure
  ///
  bool CURLAddOption(CURLOptiontype type, const std::string& name, const std::string& value)
  {
    using namespace kodi::addon;

    if (!m_file)
    {
      kodi::Log(ADDON_LOG_ERROR, "kodi::vfs::CURLCreate(...) needed to call before!");
      return false;
    }
    return CAddonBase::m_interface->toKodi->kodi_filesystem->curl_add_option(
        CAddonBase::m_interface->toKodi->kodiBase, m_file, type, name.c_str(), value.c_str());
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Open the curl file created with CURLCreate.
  ///
  /// @param[in] flags [opt] The flags to pass, see @ref OpenFileFlags
  /// @return True on success or false on failure
  ///
  bool CURLOpen(unsigned int flags = 0)
  {
    using namespace kodi::addon;

    if (!m_file)
    {
      kodi::Log(ADDON_LOG_ERROR, "kodi::vfs::CURLCreate(...) needed to call before!");
      return false;
    }
    return CAddonBase::m_interface->toKodi->kodi_filesystem->curl_open(
        CAddonBase::m_interface->toKodi->kodiBase, m_file, flags);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Read from an open file.
  ///
  /// @param[in] ptr The buffer to store the data in.
  /// @param[in] size The size of the buffer.
  /// @return number of successfully read bytes if any bytes were read and
  ///         stored in buffer, zero if no bytes are available to read (end of
  ///         file was reached) or undetectable error occur, -1 in case of any
  ///         explicit error
  ///
  ssize_t Read(void* ptr, size_t size)
  {
    using namespace kodi::addon;

    if (!m_file)
      return -1;
    return CAddonBase::m_interface->toKodi->kodi_filesystem->read_file(
        CAddonBase::m_interface->toKodi->kodiBase, m_file, ptr, size);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Read a string from an open file.
  ///
  /// @param[out] line The buffer to store the data in.
  /// @return True when a line was read, false otherwise.
  ///
  bool ReadLine(std::string& line)
  {
    using namespace kodi::addon;

    line.clear();
    if (!m_file)
      return false;
    // TODO: Read 1024 chars into buffer. If file position advanced that many
    // chars, we didn't hit a newline. Otherwise, if file position is 1 or 2
    // past the number of bytes read, we read (and skipped) a newline sequence.
    char buffer[1025];
    if (CAddonBase::m_interface->toKodi->kodi_filesystem->read_file_string(
            CAddonBase::m_interface->toKodi->kodiBase, m_file, buffer, sizeof(buffer)))
    {
      line = buffer;
      return !line.empty();
    }
    return false;
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Write to a file opened in write mode.
  ///
  /// @param[in] ptr Pointer to the data to write, converted to a <b>`const void*`</b>.
  /// @param[in] size Size of the data to write.
  /// @return number of successfully written bytes if any bytes were written,
  ///         zero if no bytes were written and no detectable error occur,-1
  ///         in case of any explicit error
  ///
  ssize_t Write(const void* ptr, size_t size)
  {
    using namespace kodi::addon;

    if (!m_file)
      return -1;
    return CAddonBase::m_interface->toKodi->kodi_filesystem->write_file(
        CAddonBase::m_interface->toKodi->kodiBase, m_file, ptr, size);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Flush buffered data.
  ///
  /// If the given stream was open for writing (or if it was open for updating
  /// and the last i/o operation was an output operation) any unwritten data
  /// in its output buffer is written to the file.
  ///
  /// The stream remains open after this call.
  ///
  /// When a file is closed, either because of a call to close or because the
  /// class is destructed, all the buffers associated with it are
  /// automatically flushed.
  ///
  void Flush()
  {
    using namespace kodi::addon;

    if (!m_file)
      return;
    CAddonBase::m_interface->toKodi->kodi_filesystem->flush_file(
        CAddonBase::m_interface->toKodi->kodiBase, m_file);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Set the file's current position.
  ///
  /// The whence argument is optional and defaults to SEEK_SET (0)
  ///
  /// @param[in] position the position that you want to seek to
  /// @param[in] whence [optional] offset relative to You can set the value of
  ///                              whence to one of three things:
  /// |   Value  | int | Description                                         |
  /// |:--------:|:---:|:----------------------------------------------------|
  /// | SEEK_SET |  0  | position is relative to the beginning of the file. This is probably what you had in mind anyway, and is the most commonly used value for whence.
  /// | SEEK_CUR |  1  | position is relative to the current file pointer position. So, in effect, you can say, "Move to my current position plus 30 bytes," or, "move to my current position minus 20 bytes."
  /// | SEEK_END |  2  | position is relative to the end of the file. Just like SEEK_SET except from the other end of the file. Be sure to use negative values for offset if you want to back up from the end of the file, instead of going past the end into oblivion.
  ///
  /// @return Returns the resulting offset location as measured in bytes from
  ///         the beginning of the file. On error, the value -1 is returned.
  ///
  int64_t Seek(int64_t position, int whence = SEEK_SET)
  {
    using namespace kodi::addon;

    if (!m_file)
      return -1;
    return CAddonBase::m_interface->toKodi->kodi_filesystem->seek_file(
        CAddonBase::m_interface->toKodi->kodiBase, m_file, position, whence);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Truncate a file to the requested size.
  ///
  /// @param[in] size The new max size.
  /// @return New size? On error, the value -1 is returned.
  ///
  int Truncate(int64_t size)
  {
    using namespace kodi::addon;

    if (!m_file)
      return -1;
    return CAddonBase::m_interface->toKodi->kodi_filesystem->truncate_file(
        CAddonBase::m_interface->toKodi->kodiBase, m_file, size);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief The current offset in an open file.
  ///
  /// @return The requested offset. On error, the value -1 is returned.
  ///
  int64_t GetPosition()
  {
    using namespace kodi::addon;

    if (!m_file)
      return -1;
    return CAddonBase::m_interface->toKodi->kodi_filesystem->get_file_position(
        CAddonBase::m_interface->toKodi->kodiBase, m_file);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Get the file size of an open file.
  ///
  /// @return The requested size. On error, the value -1 is returned.
  ///
  int64_t GetLength()
  {
    using namespace kodi::addon;

    if (!m_file)
      return -1;
    return CAddonBase::m_interface->toKodi->kodi_filesystem->get_file_length(
        CAddonBase::m_interface->toKodi->kodiBase, m_file);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Checks the file access is on end position.
  ///
  /// @return If you've reached the end of the file, AtEnd() returns true.
  ///
  bool AtEnd()
  {
    using namespace kodi::addon;

    if (!m_file)
      return true;
    int64_t length = CAddonBase::m_interface->toKodi->kodi_filesystem->get_file_length(
        CAddonBase::m_interface->toKodi->kodiBase, m_file);
    int64_t position = CAddonBase::m_interface->toKodi->kodi_filesystem->get_file_position(
        CAddonBase::m_interface->toKodi->kodiBase, m_file);
    return position >= length;
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Get the chunk size for an open file.
  ///
  /// @return The requested size. On error, the value -1 is returned.
  ///
  int GetChunkSize()
  {
    using namespace kodi::addon;

    if (!m_file)
      return -1;
    return CAddonBase::m_interface->toKodi->kodi_filesystem->get_file_chunk_size(
        CAddonBase::m_interface->toKodi->kodiBase, m_file);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Retrieve a file property.
  ///
  /// @param[in] type The type of the file property to retrieve the value for
  /// @param[in] name The name of a named property value (e.g. Header)
  /// @return value of requested property, empty on failure / non-existance
  ///
  const std::string GetPropertyValue(FilePropertyTypes type, const std::string& name) const
  {
    using namespace kodi::addon;

    if (!m_file)
    {
      kodi::Log(ADDON_LOG_ERROR,
                "kodi::vfs::CURLCreate(...) needed to call before GetPropertyValue!");
      return "";
    }
    std::vector<std::string> values = GetPropertyValues(type, name);
    if (values.empty())
    {
      return "";
    }
    return values[0];
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Retrieve file property values.
  ///
  /// @param[in] type The type of the file property values to retrieve the value for
  /// @param[in] name The name of the named property (e.g. Header)
  /// @return values of requested property, empty vector on failure / non-existance
  ///
  const std::vector<std::string> GetPropertyValues(FilePropertyTypes type,
                                                   const std::string& name) const
  {
    using namespace kodi::addon;

    if (!m_file)
    {
      kodi::Log(ADDON_LOG_ERROR,
                "kodi::vfs::CURLCreate(...) needed to call before GetPropertyValues!");
      return std::vector<std::string>();
    }
    int numValues;
    char** res(CAddonBase::m_interface->toKodi->kodi_filesystem->get_property_values(
        CAddonBase::m_interface->toKodi->kodiBase, m_file, type, name.c_str(), &numValues));
    if (res)
    {
      std::vector<std::string> vecReturn;
      for (int i = 0; i < numValues; ++i)
      {
        vecReturn.emplace_back(res[i]);
      }
      CAddonBase::m_interface->toKodi->free_string_array(CAddonBase::m_interface->toKodi->kodiBase,
                                                         res, numValues);
      return vecReturn;
    }
    return std::vector<std::string>();
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_vfs_CFile
  /// @brief Get the current download speed of file if loaded from web.
  ///
  /// @return The current download speed.
  ///
  double GetFileDownloadSpeed()
  {
    using namespace kodi::addon;

    if (!m_file)
      return 0.0;
    return CAddonBase::m_interface->toKodi->kodi_filesystem->get_file_download_speed(
        CAddonBase::m_interface->toKodi->kodiBase, m_file);
  }
  //--------------------------------------------------------------------------

private:
  void* m_file = nullptr;
};
//@}
//------------------------------------------------------------------------------

//}}}

} /* namespace vfs */
} /* namespace kodi */

#endif /* __cplusplus */
